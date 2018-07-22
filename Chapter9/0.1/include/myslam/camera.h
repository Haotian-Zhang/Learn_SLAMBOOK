//
// Created by haotian on 7/22/18.
//

#ifndef CAMERA_H
#define CAMERA_H
// Camera 类存储相机的内参和外参,并完成相机坐标系、像素坐标系、和世界坐标系
//之间的坐标变换
#include "myslam/common_include.h"

// 命名空间可以防止我们不小心定义出别的库里同名的函数,也是一种比较安全和规范的做法
namespace myslam{
// Pinhole RGBD camera model
    class Camera{
    public:
        typedef std::shared_ptr<Camera> Ptr;
        float fx_, fy_, cx_, cy_, depth_scale_; // Camera intrinsics

        Camera();
        Camera( float fx, float fy, float cx, float cy, float depth_scale = 0):
                fx_(fx), fy_(fy), cx_(cx), cy_(cy), depth_scale_(depth_scale)
        {}

        // coordinate transform
        Vector3d world2camera( const Vector3d& p_w, const SE3& T_c_w );
        Vector3d camera2world( const Vector3d& p_c, const SE3& T_c_w );
        Vector2d camera2pixel( const Vector3d& p_c );
        Vector3d pixel2camera( const Vector2d& p_p, double depth=1 );
        Vector3d pixel2world(const Vector2d& p_p, const SE3& T_c_w, double depth=1 );
        Vector2d world2pixel(const Vector3d& p_w, const SE3& T_c_w);
    };
}


#endif //CAMERA_H
