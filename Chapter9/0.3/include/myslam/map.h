//
// Created by haotian on 7/22/18.
//

#ifndef MAP_H
#define MAP_H

#include "myslam/common_include.h"
#include "myslam/frame.h"
#include "myslam/mappoint.h"

/*Map 类管理着所有的路标点,并负责添加新路标、删除不好的路标等工作
 */
namespace myslam{
    class Map{
    public:
        typedef shared_ptr<Map> Ptr;
        unordered_map<unsigned long, MapPoint::Ptr> map_points_; // all landmarks
        unordered_map<unsigned long, Frame::Ptr>    keyframes_; // all keyframes

        Map(){}

        void insertKeyFrame( Frame::Ptr frame );
        void insertMapPoint( MapPoint::Ptr map_point );
    };
}
#endif //MAP_H
