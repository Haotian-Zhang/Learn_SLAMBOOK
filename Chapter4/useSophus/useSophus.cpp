//
// Created by haotian on 7/14/18.
//

#include <iostream>
#include <ctime>
#include <Eigen/Core>
#include <Eigen/Geometry>

#include "sophus/so3.h"
#include "sophus/se3.h"

using namespace std;

int main(){
    Eigen::Matrix3d R = Eigen::AngleAxisd(M_PI/2, Eigen::Vector3d(0, 0, 1)).toRotationMatrix();

    Sophus::SO3 SO3_R(R);
    Sophus::SO3 SO3_v(0, 0, M_PI/2);
    Eigen::Quaterniond q(R);
    Sophus::SO3 SO3_q(q);

    cout << "SO(3) from matrix: " << SO3_R << endl;
    cout <<  "SO(3) from vector " << SO3_v << endl;
    cout << "SO(3) from quaternion " << SO3_q << endl;

    Eigen::Vector3d so3 = SO3_R.log();
    cout << "so3 = " << so3.transpose() << endl;

    cout << "so3 hat" << Sophus::SO3::vee( Sophus::SO3::hat(so3) ).transpose() << endl;

    Eigen::Vector3d update_so3(1e-4, 0, 0);
    Sophus::SO3 SO3_updated = Sophus::SO3::exp(update_so3)*SO3_R;
    cout << "SO3_updated " << SO3_updated << endl;

    cout << "==============SE3=================" << endl;
    Eigen::Vector3d t(1, 0, 0);
    Sophus::SE3 SE3_Rt(R, t);
    Sophus::SE3 SE3_qt(q, t);

    cout << "SE3 from R, t" << SE3_Rt << endl;
    cout << "SE3 from q, t" << SE3_qt << endl;

    typedef Eigen::Matrix <double, 6, 1> Vector6d;
    Vector6d se3 = SE3_Rt.log();
    cout << "se3 = " << se3.transpose() << endl;

    cout << "se3 hat" << Sophus::SE3::hat(se3) << endl;
    cout << "se3 vee" << Sophus::SE3::vee( Sophus::SE3::hat(se3) ).transpose() << endl;

    Vector6d updated_se3;
    updated_se3.setZero();
    updated_se3(0, 0) = 1e-4d;
    Sophus::SE3 SE3_updated = Sophus::SE3::exp(updated_se3)*SE3_Rt;
    cout << "SE3 udpated " << endl << SE3_updated.matrix() << endl;

    return 0;
}
