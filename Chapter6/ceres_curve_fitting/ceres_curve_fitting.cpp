//
// Created by haotian on 7/17/18.
//

#include <iostream>
#include <opencv2/core/core.hpp>
#include <ceres/ceres.h>
#include <chrono>

using namespace std;

// COST FUNCTION MODEL
// 1. 定义 Cost Function 模型。方法是书写一个类,并在类中定义带模板参数的 () 运算
// 符,这样该类成为了一个拟函数(Functor,C++ 术语)。这种定义方式使得 Ceres
// 可以像调用函数一样,对该类的某个对象(比如说 a)调用 a<double>() 方法——
// 这使对象具有像函数那样的行为
struct CURVE_FITTING_COST{
    CURVE_FITTING_COST ( double x, double y ) : _x ( x ), _y ( y ) {}

    template <typename T>
    bool operator() (
            const T* const abc, // Model parameters, 3 dimensions
            T* residual ) const // residue
    {
        //y - exp(ax^2+bx+c)
        residual[0] = T(_y) - ceres::exp( abc[0]*T(_x)*T(_x) + abc[1]*T(_x) + abc[2] );
        return true;
    }
    const double _x, _y; // x,y are data
};

int main(){
    double a = 1.0, b = 2.0, c = 1.0;
    int N = 100;
    double w_sigma = 1.0;
    cv::RNG rng; //OpenCV random number generator
    double abc[3] = {0, 0, 0};

    vector<double> x_data, y_data;

    cout << "generating data: " << endl;

    for (int i = 0; i < N; i++) {
        double x = i / 100.0;
        x_data.push_back( x );
        y_data.push_back(
                exp( a*x*x + b*x + c) + rng.gaussian( w_sigma )
                );
        cout << x_data[i] << " " << y_data[i] << endl;
    }

//    调用 AddResidualBlock 将误差项添加到目标函数中。由于优化需要梯度,我们有若干种选择:
//    (1)使用 Ceres 的自动求导(Auto Diff);
//    (2)使用数值求导(Numeric Diff);
//    (3)自行推导解析的导数形式,提供给 Ceres。其中自动求导在编码上是最方
//    便的,于是我们就使用自动求导啦!

    ceres::Problem problem;
    for (int j = 0; j < N; j++) {
        problem.AddResidualBlock(
//                自动求导需要指定误差项和优化变量的维度。这里的误差则是标量,维度为 1;优化
//                的是 a, b, c 三个量,维度为 3。于是,在自动求导类的模板参数中设定变量维度为 1,3。
                new ceres::AutoDiffCostFunction<CURVE_FITTING_COST, 1, 3>(
                        new CURVE_FITTING_COST ( x_data[j], y_data[j] )
                        ),
                nullptr, //core function, not used here
                abc // estimated parameters
                );
    }

//    设定好问题后,调用 solve 函数进行求解。你可以在 option 里配置(非常详细的)优
//    化选项。例如,我们可以选择使用 Line Search 还是 Trust Region,迭代次数,步长
//    等等。读者可以查看 Options 的定义,看看有哪些优化方法可选,当然默认的配置已
//    经可以用在很广泛的问题上了。
    ceres::Solver::Options options; // FIll in options
    options.linear_solver_type = ceres::DENSE_QR; // How to solve increment functions
    options.minimizer_progress_to_stdout = true;

    ceres::Solver::Summary summary; // Opimization summary
    chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
    ceres::Solve( options, &problem, &summary ); //Start Optimization
    chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
    chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<double>>( t2 - t1 );
    cout << "solve time cost = " << time_used.count() << "seconds" << endl;

    cout << summary.BriefReport() << endl;
    cout << "estimated a, b, c = ";
    for (auto a:abc ) cout<<a<<" ";
    cout << endl;
    // visualization

    return 0;
}
