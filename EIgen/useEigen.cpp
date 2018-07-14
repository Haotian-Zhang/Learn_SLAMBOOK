//
// Created by haotian on 7/13/18.
//

#include <iostream>
#include <ctime>
using namespace std;

#include <Eigen/Core>
#include <Eigen/Dense>

#define MATRIX_SIZE 50

int main(){
    Eigen::Matrix<float, 2, 3> matrix_23;

    Eigen::Vector3d v_3d;

    Eigen::Matrix3d matrix_33 = Eigen::Matrix3d::Zero();

    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> matrix_dynamic;

    Eigen::MatrixXd matrix_x;

    matrix_23 << 1, 2, 3, 4, 5, 6;
    cout << matrix_23 << endl;

    for (int i = 0; i < 1; i++){
        for (int j = 0; j < 2; j++){
            cout << matrix_23(i,j) << endl;
        }
    }

    v_3d << 3, 2, 1;
//    cout << v_3d << endl;
    Eigen::Matrix<double,2,1> result = matrix_23.cast<double>() * v_3d;
    cout << result << endl;

    matrix_33 = Eigen::Matrix3d::Random();
    cout << matrix_33 << endl;

    cout << matrix_33.transpose() << endl;
    cout << matrix_33.sum() << endl;
    cout << matrix_33.trace() << endl;
    cout << 10 * matrix_33 << endl;
    cout << matrix_33.inverse() << endl;
    cout << matrix_33.determinant() << endl;

    cout << "===========" << endl;
    Eigen::SelfAdjointEigenSolver<Eigen::Matrix3d> eigen_solver ( matrix_33 );
    cout << "Eigen Values = " << eigen_solver.eigenvalues() << endl;
    cout << "Eigen vectors = " << eigen_solver.eigenvectors() << endl;

    Eigen::Matrix<double, MATRIX_SIZE, MATRIX_SIZE> matrix_nn;
    matrix_nn = Eigen::MatrixXd::Random(MATRIX_SIZE, MATRIX_SIZE);

    Eigen::Matrix<double, MATRIX_SIZE, 1> v_nd;
    v_nd = Eigen::MatrixXd::Random(MATRIX_SIZE, 1);

    clock_t time_stt = clock();
    Eigen::Matrix<double, MATRIX_SIZE,1> x = matrix_nn.inverse() * v_nd;
    cout <<"time use in normal inverse is " << 1000* (clock() - time_stt)/(double)CLOCKS_PER_SEC << "ms"<< endl;

    time_stt = clock();
    x = matrix_nn.colPivHouseholderQr().solve(v_nd);
    cout <<"time use in normal inverse is " << 1000* (clock() - time_stt)/(double)CLOCKS_PER_SEC << "ms"<< endl;

    //*课后习题3
    Eigen::Matrix<double, 5, 8> big_matrix = Eigen::Matrix<double, 5, 8>::Random();
    Eigen::Matrix3d I_33 = big_matrix.block(0, 0, 3, 3);
    I_33 = Eigen::Matrix3d::Identity();
    cout << I_33 << endl;
    return 0;
}