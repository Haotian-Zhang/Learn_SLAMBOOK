//
// Created by haotian on 7/22/18.
//

#ifndef FRAME_H
#define FRAME_H

#include "myslam/common_include.h"
#include "myslam/camera.h"
/*
 * 定义了 ID、时间戳、位姿、相机、图像这几个量,这应该是一个帧当中含有的最重要的信息。
 * 在方法中,提取了几个重要的方法:创建 Frame、寻找给定点对应的深度、获取相机光心、判断某个点是否在视野内等等。
 */
namespace myslam {
    class MapPoint;
    class Frame {
    public:
        typedef std::shared_ptr<Frame> Ptr;
        unsigned long id_; // id of this frame
        double time_stamp_; // when it is recorded
        SE3 T_c_w_; // transform from world to camra
        Camera::Ptr camera_; // Pinhole RGB-D Camera model
        Mat color_, depth_; // color and depth image
    public:
        Frame();

        Frame(long id, double time_stamp = 0, SE3 T_c_w = SE3(), Camera::Ptr camera = nullptr, Mat color = Mat(),
              Mat depth = Mat());

        ~Frame();

        // factory function
        static Frame::Ptr createFrame();

        // find the depth in depth map
        double findDepth(const cv::KeyPoint &kp);

        // Get camera Center
        Vector3d getCamCenter() const;

        // check if a point is in this frame
        bool isInFrame(const Vector3d &pt_world);

    };

}

#endif //FRAME_H
