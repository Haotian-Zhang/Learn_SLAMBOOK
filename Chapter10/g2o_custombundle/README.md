# Bundle Adjustment
This prorject is to use G2O to do the Bundle Adjustment. The results are shown in the following:

(The left is the cloud points before BA, and the right shows the cloud points after BA.)

<div align="center">
<img src="https://github.com/Haotian-Zhang/Learn_SLAMBOOK/raw/master/Chapter10/g2o_custombundle/initial.png" height="300px" alt="Before BA" > 
<img src="https://github.com/Haotian-Zhang/Learn_SLAMBOOK/raw/master/Chapter10/g2o_custombundle/final.png" height="300px" alt="After BA" >
</div>

## How to run the codes

### Building
```
mkdir build
cd ./build
cmake ..
make
```

### Usage
```
cd ./build
./g2o_customBundle -input ../data/problem-.....txt
```

##### See more detail settings by
```
./g2o_customBundle -help
```

## Caution
g2o 在做 Bundle Adjustment 的优化时必须要将其所有点云全部 Schur 掉,否则会出错！其原因在于我们使用了g2o::LinearSolver<BalBlockSolver::PoseMatrixType> 这个类型来指定 linearsolver，模板参数当中的 PoseMatrixType 在程序中为相机姿态参数的维度，那么 Bundle Adjustment 当中 Schur 消元后解的线性方程组必须时只含有相机姿态变量。
