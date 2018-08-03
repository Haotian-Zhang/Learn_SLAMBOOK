//
// Created by haotian on 8/3/18.
//

#include <iostream>
#include <fstream>
using namespace std;

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <Eigen/Core>
#include <Eigen/Geometry>

#include <boost/format.hpp>

#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/filters/statistical_outlier_removal.h>

int main(int argc, char** argv){
    vector<cv::Mat> colorImgs, depthImgs; // rgb and depth images
    vector<Eigen::Isometry3d> poses;      // camera poses

    ifstream fin("../data/pose.txt");
    if (!fin){
        cerr << "cannot find pose file." << endl;
    }

    for ( int i=0; i<5; i++ )
    {
        boost::format fmt( "../data/%s/%d.%s" ); // lambda format
        colorImgs.push_back( cv::imread( (fmt%"color"%(i+1)%"png").str() ));
        depthImgs.push_back( cv::imread( (fmt%"depth"%(i+1)%"pgm").str(), -1 )); // 使用-1读取原始图像

        double data[7] = {0};
        for ( int i=0; i<7; i++ ) {
            fin>>data[i];
        }
        Eigen::Quaterniond q( data[6], data[3], data[4], data[5] );
        Eigen::Isometry3d T(q);
        T.pretranslate( Eigen::Vector3d( data[0], data[1], data[2] ));
        poses.push_back( T );
    }

    double cx = 325.5;
    double cy = 253.5;
    double fx = 518.0;
    double fy = 519.0;
    double depthScale = 1000.0;

    cout << "turing the image into pointcloud... " << endl;

    typedef pcl::PointXYZRGB PointT;
    typedef pcl::PointCloud<PointT> PointCloud;

    // create a new pointcloud map
    PointCloud::Ptr pointCloud( new PointCloud );
    for (int i = 0; i < 5; i++) {
        PointCloud::Ptr current( new PointCloud );
        cout << "turning... " << i+1 << endl;
        cv::Mat color = colorImgs[i];
        cv::Mat depth = depthImgs[i];
        Eigen::Isometry3d T = poses[i];

        for (int v = 0; v < color.rows; v++) {
            for (int u = 0; u < color.cols; u++) {
                unsigned int d = depth.ptr<unsigned short>(v)[u]; // depth value
                if (d == 0 ) continue;
                if (d >= 7000) continue;
                Eigen::Vector3d point;
                point[2] = double(d) / depthScale;
                point[0] = (u-cx)*point[2]/fx;
                point[1] = (v-cy)*point[2]/fy;
                Eigen::Vector3d pointWorld = T * point;

                PointT p;
                p.x = pointWorld[0];
                p.y = pointWorld[1];
                p.z = pointWorld[2];
                p.b = color.data[ v*color.step+u*color.channels() ];
                p.g = color.data[ v*color.step+u*color.channels()+1 ];
                p.r = color.data[ v*color.step+u*color.channels()+2 ];
                current->points.push_back( p );
            }
        }
        // depth filter and statistical removal
        PointCloud::Ptr tmp ( new PointCloud );
        pcl::StatisticalOutlierRemoval<PointT> statistical_filter;
        statistical_filter.setMeanK(50);
        statistical_filter.setStddevMulThresh(1.0);
        statistical_filter.setInputCloud(current);
        statistical_filter.filter( *tmp );
        (*pointCloud) += *tmp;
    }

    pointCloud->is_dense = false;
    cout << "the point cloud has " << pointCloud->size() << " points" << endl;

    // voxel filter
    pcl::VoxelGrid<PointT> voxel_filter;
    voxel_filter.setLeafSize( 0.01, 0.01, 0.01 );   // set resolution
    PointCloud::Ptr tmp ( new PointCloud );
    voxel_filter.setInputCloud( pointCloud );
    voxel_filter.filter( *tmp );
    tmp->swap( *pointCloud );

    cout << "after filtering, the point cloud has " << pointCloud->size() << " points" << endl;

    pcl::io::savePCDFileBinary("../map.pcd", *pointCloud );
    return 0;
}