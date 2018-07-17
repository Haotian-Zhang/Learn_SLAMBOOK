//
// Created by haotian on 7/17/18.
//
#include <iostream>
#include <g2o/core/base_vertex.h>
#include <g2o/core/base_unary_edge.h>
#include <g2o/core/block_solver.h>
#include <g2o/core/optimization_algorithm_levenberg.h>
#include <g2o/core/optimization_algorithm_dogleg.h>
#include <g2o/core/optimization_algorithm_gauss_newton.h>
#include <g2o/solvers/dense/linear_solver_dense.h>
#include <Eigen/Core>
#include <opencv2/core/core.hpp>
#include <cmath>
#include <chrono>

using namespace std;

//1. 定义顶点和边的类型;
//2. 构建图;
//3. 选择优化算法;
//4. 调用 g2o 进行优化,返回结果。

// Vertex Template, Parameters: data dimensions, and data type
class CurveFittingVertex: public g2o::BaseVertex<3, Eigen::Vector3d> {
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    virtual void setToOriginImpl() // reset
    {
        _estimate << 0, 0, 0;
    }

    virtual void oplusImpl( const double* update){
        _estimate += Eigen::Vector3d(update); //update
    }
    //read and write, NULL
    virtual bool read( istream& in){}
    virtual bool write( ostream& out) const {}
};

// Error Template, Parameters: observation dimensions, type, Vertex type
class CurveFittingEdge: public g2o::BaseUnaryEdge<1, double, CurveFittingVertex>{
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    CurveFittingEdge( double x ): BaseUnaryEdge(), _x(x) {}
    void computeError(){
        const CurveFittingVertex* v = static_cast<const CurveFittingVertex*> (_vertices[0]);
        const Eigen::Vector3d abc = v -> estimate();
        _error(0, 0) = _measurement - std::exp( abc(0,0)*_x*_x + abc(1, 0)*_x + abc(2,0) );
    }
    virtual bool read(istream& in) {}
    virtual bool write(ostream& out) const {}

public:
    double _x; // x value, y _measurement
};
int main(int argc, char** argv){

    double a = 1.0, b = 2.0, c = 1.0;
    int N = 100;
    double w_sigma = 1.0;
    cv::RNG rng;
    double abc[3] = {0, 0, 0};

    vector<double> x_data, y_data;

    cout << "generating data: " << endl;
    for (int i = 0; i < 100; i++){
        double x = i / 100.0;
        x_data.push_back( x );
        y_data.push_back(
                exp( a*x*x + b*x + c ) + rng.gaussian( w_sigma )
                );
        cout << x_data[i] << " " << y_data[i] << endl;
    }

    // Matrix block: Error Item <3, 1>
    typedef g2o::BlockSolver< g2o::BlockSolverTraits <3,1> > Block;
    // Solver, Dense
    Block::LinearSolverType* linearSolver = new g2o::LinearSolverDense<Block::PoseMatrixType>();
    Block* solve_ptr = new Block( linearSolver );

    // 梯度下降法
//    g2o::OptimizationAlgorithmLevenberg* solver = new g2o::OptimizationAlgorithmLevenberg( solve_ptr );
//    g2o::OptimizationAlgorithmGaussNewton* solver = new g2o::OptimizationAlgorithmGaussNewton( solve_ptr );
    g2o::OptimizationAlgorithmDogleg* solver = new g2o::OptimizationAlgorithmDogleg( solve_ptr );

    g2o::SparseOptimizer optimizer; // graph model
    optimizer.setAlgorithm( solver );  // set solver
    optimizer.setVerbose( true ); // verbose

    // Add in Vertices
    CurveFittingVertex *v = new CurveFittingVertex();
    v->setEstimate( Eigen::Vector3d(0, 0, 0));
    v->setId(0);
    optimizer.addVertex( v );

    for (int i = 0; i < 100; i++) {
        CurveFittingEdge* edge = new CurveFittingEdge( x_data[i] );
        edge->setId(i);
        edge->setVertex(0, v);
        edge->setMeasurement( y_data[i] );
        //information matrix
        edge->setInformation( Eigen::Matrix<double, 1, 1>::Identity()*1/(w_sigma*w_sigma) );
        optimizer.addEdge( edge );
    }

    cout << "start optimization" << endl;
    chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
    optimizer.initializeOptimization();
    optimizer.optimize(100);
    chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
    chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<double>>( t2 - t1);
    cout << "solve time cost = " << time_used.count() << "seconds" << endl;

    //output optimal value
    Eigen::Vector3d abc_estimate = v->estimate();
    cout << "estimated model: " << abc_estimate.transpose() << endl;

    return 0;
}