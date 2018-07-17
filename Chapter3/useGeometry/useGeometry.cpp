//
// Created by haotian on 7/14/18.
//

#include <iostream>

#include <Eigen/Geometry>
#include <Eigen/Core>
#include <Eigen/Dense>

#include <ctime>
using namespace std;

int main(){
    //旋转向量
    Eigen::Matrix3d rotation_matrix = Eigen::Matrix3d::Identity();
    Eigen::AngleAxisd rotation_vector (M_PI/4, Eigen::Vector3d (0, 0 , 1));
    cout .precision(3);
    cout << "rotation matrix = \n" << rotation_vector.matrix() << endl;

    rotation_matrix = rotation_vector.toRotationMatrix();
    Eigen::Vector3d v (1, 0, 0);
    Eigen::Vector3d v_rotated = rotation_matrix * v;
    cout << "(1, 0, 0) after rotation = " << v_rotated.transpose() << endl;

    v_rotated = rotation_vector * v;
    cout << "(1, 0, 0) after rotation = " << v_rotated.transpose() << endl;

    //欧拉角
    Eigen::Vector3d euler_angles = rotation_matrix.eulerAngles( 2, 1, 0);
    cout << "yaw pitch roll = " << euler_angles.transpose() << endl;

    //欧式变换使用Eigen::Isometry
    Eigen::Isometry3d T = Eigen::Isometry3d::Identity();
    T.rotate( rotation_vector );
    T.pretranslate( Eigen::Vector3d (1,3,4));
    cout << "Transform matrix = \n" << T.matrix() << endl;

    Eigen::Vector3d v_transformed = T * v;
    cout << "v transformed = " << v_transformed.transpose() << endl;

    Eigen::Quaterniond q = Eigen::Quaterniond (rotation_vector);
    cout << "quaterniod = " << q.coeffs().transpose() << endl;

    q = Eigen::Quaterniond (rotation_matrix);
    cout << "quaterniod = " << q.coeffs().transpose() << endl;

    v_rotated = q * v;
    cout << "(1, 0, 0) after rotation = " << v_rotated.transpose() << endl;

    //* 课后习题7
    //四元数初始化为(w, x, y, z)
    Eigen::Quaterniond q1(0.35, 0.2, 0.3, 0.1);
    q1.normalize();
    Eigen::Vector3d t2(0.3, 0.1, 0.1);

    Eigen::Quaterniond q2(-0.5, 0.4, -0.1, 0.2);
    q2.normalize();
    Eigen::Vector3d t(-0.1, 0.5, 0.3);

//  T_cw为小萝卜在一号坐标系下的旋转矩阵
    Eigen::Isometry3d T_cw = Eigen::Isometry3d::Identity();
    T_cw.prerotate(q1);
    T_cw.pretranslate(t2);

    Eigen::Vector3d p(0.5, 0, 0.2);
    //得到P点的世界坐标系
    Eigen::Vector3d pw = T_cw.inverse() * p;

//  T_cw2位小萝卜在二号坐标系下的旋转矩阵
    Eigen::Isometry3d T_cw2 = Eigen::Isometry3d::Identity();
    T_cw2.prerotate(q2);
    T_cw2.pretranslate(t);

//    得到小萝卜在二号坐标系下的位置
    Eigen::Vector3d p2 = Eigen::Vector3d::Zero();
    p2 = T_cw2 * pw;

    cout << "小萝卜二号坐标系下的坐标 = " << p2.transpose() << endl;







;    return 0;
}