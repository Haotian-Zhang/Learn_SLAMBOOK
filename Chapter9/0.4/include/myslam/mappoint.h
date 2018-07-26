//
// Created by haotian on 7/22/18.
//

#ifndef MAPPOINT_H
#define MAPPOINT_H

#include "myslam/common_include.h"
/*
 * MapPoint 表示路标点。我们将估计它的世界坐标,并且我们会拿当前帧提取到的特
征点与地图中的路标点匹配,来估计相机的运动,因此还需要存储它对应的描述子。
 */
namespace myslam{
    class Frame;
    class MapPoint
    {
    public:
        typedef shared_ptr<MapPoint> Ptr;
        unsigned long      id_;        // ID
        static unsigned long factory_id_;    // factory id
        bool        good_;      // wheter a good point
        Vector3d    pos_;       // Position in world
        Vector3d    norm_;      // Normal of viewing direction
        Mat         descriptor_; // Descriptor for matching

        list<Frame*>    observed_frames_;   // key-frames that can observe this point

        int         matched_times_;     // being an inliner in pose estimation
        int         visible_times_;     // being visible in current frame

        MapPoint();
        MapPoint(
                unsigned long id,
                const Vector3d& position,
                const Vector3d& norm,
                Frame* frame=nullptr,
                const Mat& descriptor=Mat()
        );

        inline cv::Point3f getPositionCV() const {
            return cv::Point3f( pos_(0,0), pos_(1,0), pos_(2,0) );
        }

        static MapPoint::Ptr createMapPoint();
        static MapPoint::Ptr createMapPoint(
                const Vector3d& pos_world,
                const Vector3d& norm_,
                const Mat& descriptor,
                Frame* frame );
    };
}

#endif //MAPPOINT_H
