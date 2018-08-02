# Bundle Adjustment - Ceres
This prorject is to use Ceres to do the Bundle Adjustment. The results are shown in the following (almost the same as we did using G2O):

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
./ceres_customBundle -input ../data/problem-.....txt
```

##### See more detail settings by
```
./ceres_customBundle -help
```

## Caution
Ceres 库公开的 API 说明详细，同时源代码可读性也高，推荐多多阅读 Ceres 源代码，并且自己尝试在 Schur 消元操作中只消去部分点云变量，或者夹杂着消去一些相机变量。这只需要操作 ceres::ParameterBlockOrdering::AddElementToGroup 函数,在对应变量地址上,用序号指定顺序即可。

### Related Materials - Ceres
1）[Ceres Solver](http://www.ceres-solver.org/index.html)

（2）[Ceres-Solver学习笔记(1)](http://blog.csdn.net/huajun998/article/details/76136710)

（3）[Ceres-Solver学习笔记(2)](http://blog.csdn.net/huajun998/article/details/76145441)

（4）[Ceres-Solver学习笔记(3)](http://blog.csdn.net/huajun998/article/details/76165511)

（5）[Ceres-Solver学习笔记(4)](http://blog.csdn.net/huajun998/article/details/76166307)

（6）[Ceres-Solver学习笔记(5)](http://blog.csdn.net/huajun998/article/details/76177592)

（7）[Ceres-Solver学习笔记(6)](http://blog.csdn.net/huajun998/article/details/76222745)

（8）[Ceres-Solver学习笔记(7)](http://blog.csdn.net/huajun998/article/details/76271938)

（9）[Ceres-Solver学习笔记(8)](http://blog.csdn.net/huajun998/article/details/76341292)

（10）[Ceres-Solver学习笔记(9)](http://blog.csdn.net/huajun998/article/details/76423003)
