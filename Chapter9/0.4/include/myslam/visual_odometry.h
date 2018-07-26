//
// Created by haotian on 7/23/18.
//

#ifndef VISUAL_ODOMETRY_H
#define VISUAL_ODOMETRY_H
/*
 * 1. 对新来的当前帧,提取关键点和描述子。
 * 2. 如果系统未初始化,以该帧为参考帧,根据深度图计算关键点的 3D 位置,返回
 * 3. 估计参考帧与当前帧间的运动。
 * 4. 判断上述估计是否成功。
 * 5. 若成功,把当前帧作为新的参考帧,回 1。
 * 6. 若失败,计连续丢失帧数。当连续丢失超过一定帧数,置 VO 状态为丢失,算法
结束。若未超过,返回 1。
 */
#include "myslam/common_include.h"
#include "myslam/map.h"

#include <opencv2/features2d/features2d.hpp>

namespace myslam{
    class VisualOdometry
    {
    public:
        typedef shared_ptr<VisualOdometry> Ptr;
        enum VOState {
            INITIALIZING=-1,
            OK=0,
            LOST
        };

        VOState     state_;     // current VO status
        Map::Ptr    map_;       // map with all frames and map points

        Frame::Ptr  ref_;       // reference key-frame
        Frame::Ptr  curr_;      // current frame

        cv::Ptr<cv::ORB> orb_;  // orb detector and computer
        vector<cv::KeyPoint>    keypoints_curr_;    // keypoints in current frame
        Mat                     descriptors_curr_;  // descriptor in current frame

        cv::FlannBasedMatcher   matcher_flann_;     // flann matcher
        vector<MapPoint::Ptr>   match_3dpts_;       // matched 3d points
        vector<int>             match_2dkp_index_;  // matched 2d pixels (index of kp_curr)

        SE3 T_c_w_estimated_;    // the estimated pose of current frame
        int num_inliers_;        // number of inlier features in icp
        int num_lost_;           // number of lost times

        // parameters
        int num_of_features_;   // number of features
        double scale_factor_;   // scale in image pyramid
        int level_pyramid_;     // number of pyramid levels
        float match_ratio_;     // ratio for selecting  good matches
        int max_num_lost_;      // max number of continuous lost times
        int min_inliers_;       // minimum inliers
        double key_frame_min_rot;   // minimal rotation of two key-frames
        double key_frame_min_trans; // minimal translation of two key-frames
        double  map_point_erase_ratio_; // remove map point ratio

    public: // functions
        VisualOdometry();
        ~VisualOdometry();

        bool addFrame( Frame::Ptr frame );      // add a new frame

    protected:
        // inner operation
        void extractKeyPoints();
        void computeDescriptors();
        void featureMatching();
        void poseEstimationPnP();
        void optimizeMap();

        void addKeyFrame();
        void addMapPoints();
        bool checkEstimatedPose();
        bool checkKeyFrame();

        double getViewAngle( Frame::Ptr frame, MapPoint::Ptr point );
    };
}

#endif //VISUAL_ODOMETRY_H
