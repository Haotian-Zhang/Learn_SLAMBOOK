//
// Created by haotian on 7/19/18.
//
#include <fstream>
#include "common.h"

/* RGBD Semi-Dense Direct Sparse
*/
int main ( int argc, char** argv ) {
    if ( argc != 2 )
    {
        cout<<"usage: useLK path_to_dataset"<<endl;
        return 1;
    }
    srand ( ( unsigned int ) time ( 0 ) );
    string path_to_dataset = argv[1];
    string associate_file = path_to_dataset + "/associate.txt";

    ifstream fin ( associate_file );

    string rgb_file, depth_file, time_rgb, time_depth;
    cv::Mat color, depth, gray;
    vector<Measurement> measurements;

    // camera intrinsics
    float cx = 325.5;
    float cy = 253.5;
    float fx = 518.0;
    float fy = 519.0;
    float depth_scale = 1000.0;
    Eigen::Matrix3f K;
    K<<fx, 0.f, cx, 0.f, fy, cy, 0.f, 0.f, 1.0f;

    Eigen::Isometry3d Tcw = Eigen::Isometry3d::Identity();

    cv::Mat prev_color;
    // use the first frame as the reference
    for ( int index=0; index<10; index++ ) {
        cout<<"*********** loop "<<index<<" ************"<<endl;
        fin>>time_rgb>>rgb_file>>time_depth>>depth_file;
        color = cv::imread ( path_to_dataset+"/"+rgb_file );
        depth = cv::imread ( path_to_dataset+"/"+depth_file, -1 );
        if ( color.data==nullptr || depth.data==nullptr )
            continue;
        cv::cvtColor ( color, gray, cv::COLOR_BGR2GRAY );
        // we choose points whose gradients are big
        if (index == 0){
            for (int x = 10; x < gray.cols - 10; x++){
                for (int y = 10; y < gray.rows - 10; y++){
                    Eigen::Vector2d delta(
                            gray.ptr<uchar>(y)[x+1] - gray.ptr<uchar>(y)[x-1],
                                    gray.ptr<uchar>(y+1)[x] - gray.ptr<uchar>(y-1)[x]
                            );
                    if (delta.norm() < 50)
                        continue;
                    ushort d = depth.ptr<ushort>(y)[x];
                    if (d == 0)
                        continue;
                    Eigen::Vector3d p3d = project2Dto3D(x, y, d, fx, fy, cx, cy, depth_scale);
                    float grayscale = float(gray.ptr<uchar>(y)[x]);
                    measurements.push_back(Measurement(p3d, grayscale));
                }
            }
            prev_color = color.clone();
            continue;
        }

        // use direct method to compute the camera motions
        chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
        poseEstimationDirect ( measurements, &gray, K, Tcw );
        chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
        chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<double>> ( t2-t1 );
        cout<<"Semi dense direct method costs time: "<<time_used.count() <<" seconds."<<endl;
        cout<<"Tcw="<<Tcw.matrix() <<endl;

        // plot the feature points
        cv::Mat img_show ( color.rows*2, color.cols, CV_8UC3 );
        prev_color.copyTo ( img_show ( cv::Rect ( 0,0,color.cols, color.rows ) ) );
        color.copyTo ( img_show ( cv::Rect ( 0,color.rows,color.cols, color.rows ) ) );
        for ( Measurement m:measurements ) {
            if (rand() > RAND_MAX / 5)
                continue;
            Eigen::Vector3d p = m.pos_world;
            Eigen::Vector2d pixel_prev = project3Dto2D(p(0, 0), p(1, 0), p(2, 0), fx, fy, cx, cy);
            Eigen::Vector3d p2 = Tcw * m.pos_world;
            Eigen::Vector2d pixel_now = project3Dto2D(p2(0, 0), p2(1, 0), p2(2, 0), fx, fy, cx, cy);
            if (pixel_now(0, 0) < 0 || pixel_now(0, 0) >= color.cols || pixel_now(1, 0) < 0 ||
                pixel_now(1, 0) >= color.rows)
                continue;

            float b = 0;
            float g = 250;
            float r = 0;
            img_show.ptr<uchar>(pixel_prev(1, 0))[int(pixel_prev(0, 0)) * 3] = b;
            img_show.ptr<uchar>(pixel_prev(1, 0))[int(pixel_prev(0, 0)) * 3 + 1] = g;
            img_show.ptr<uchar>(pixel_prev(1, 0))[int(pixel_prev(0, 0)) * 3 + 2] = r;

            img_show.ptr<uchar>(pixel_now(1, 0) + color.rows)[int(pixel_now(0, 0)) * 3] = b;
            img_show.ptr<uchar>(pixel_now(1, 0) + color.rows)[int(pixel_now(0, 0)) * 3 + 1] = g;
            img_show.ptr<uchar>(pixel_now(1, 0) + color.rows)[int(pixel_now(0, 0)) * 3 + 2] = r;
            cv::circle(img_show, cv::Point2d(pixel_prev(0, 0), pixel_prev(1, 0)), 4, cv::Scalar(b, g, r), 2);
            cv::circle(img_show, cv::Point2d(pixel_now(0, 0), pixel_now(1, 0) + color.rows), 4, cv::Scalar(b, g, r), 2);
        }
        cv::imshow ( "Semi-dense direct result", img_show );
        cv::waitKey ( 0 );

    }
    return 0;
}