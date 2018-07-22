//
// Created by haotian on 7/19/18.
//

/* Optical Flow
 * 光流法可以加速基于特征点的视觉里程计算法,避免计算和匹配描述子的过程,但要求相机运动较慢
 */

#include <iostream>
#include <chrono>
#include <fstream>
#include <list>
#include <vector>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/video/tracking.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
    if (argc != 2 ) {
        cout << "usage: LKFlow path_to_dataset" << endl;
        return 1;
    }
    string path_to_dataset = argv[1];
    cout << path_to_dataset << endl;
    string associate_file = path_to_dataset + "/associate.txt";
    ifstream fin( associate_file );
    string rgb_file, depth_file, time_rgb, time_depth;
    list<cv::Point2f> keypoints; //we will delete the untracked points later
    cv::Mat color, depth, last_color;
    for (int index = 0; index < 100 ; index++) {
        fin >> time_rgb >> rgb_file >> time_depth >> depth_file;
        color = cv::imread( path_to_dataset + "/" + rgb_file );
        depth = cv::imread( path_to_dataset + "/" + depth_file );
        if (index == 0){
            // the first frame
            // use FAST detector
            vector<cv::KeyPoint> kps;
//            FAST Keypoints
            cv::Ptr<cv::FastFeatureDetector> detector = cv::FastFeatureDetector::create();
//            ORB Keypoints
//            cv::Ptr<cv::FeatureDetector> detector = cv::ORB::create();
            detector->detect(color, kps);
            for (auto kp:kps ){
                keypoints.push_back( kp.pt );
            }
            last_color = color;
            continue;
        }
        if (color.data == nullptr || depth.data == nullptr )
            continue;
        vector<cv::Point2f> next_keypoints;
        vector<cv::Point2f> prev_keypoints;
        for (auto kp:keypoints )
            prev_keypoints.push_back(kp);
        vector<unsigned char> status;
        vector<float> error;
        chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
        cv::calcOpticalFlowPyrLK( last_color, color, prev_keypoints, next_keypoints, status, error );
        chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
        chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<double>>( t2 - t1 );
        cout << "LK Flow use time: " << time_used.count() << " seconds." << endl;

        // delete untracked poins
        int i = 0;
        for (auto iter=keypoints.begin(); iter != keypoints.end(); i++){
            if ( status[i] == 0 ){
                iter = keypoints.erase(iter);
                continue;
            }
            *iter = next_keypoints[i];
            iter++;
        }
        cout<<"tracked keypoints: " << keypoints.size() << endl;
        if (keypoints.size() == 0){
            cout << "all keypoints are lost." << endl;
            break;
        }
        // draw keypoints
        cv::Mat img_show = color.clone();
        for (auto kp:keypoints ) {
            cv::circle(img_show, kp, 10, cv::Scalar(0, 240, 0), 1);
        }
        cv::imshow("colors", img_show);
        cv::waitKey(0);
        last_color = color;
    }

    return 0;
}


