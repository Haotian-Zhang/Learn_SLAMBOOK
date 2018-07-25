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
    class MapPoint{
    public:
        typedef shared_ptr<MapPoint> Ptr;
        unsigned long id_;  // ID
        Vector3d pos_;      // Position in world
        Vector3d norm_;     // Normal of viewing direction
        Mat descriptor_;    // Descriptor for matching
        int observed_times_;// being observed by feature matching algo
        int correct_times_; // being an inliner in pose eltimation

        MapPoint();
        MapPoint( long id, Vector3d position, Vector3d norm );

        // factory function
        static MapPoint::Ptr createMapPoint();
    };
}

#endif //MAPPOINT_H
