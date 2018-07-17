
g2o - General Graph Optimization
================================
[![Build Status](https://travis-ci.org/RainerKuemmerle/g2o.svg?branch=master)](https://travis-ci.org/RainerKuemmerle/g2o)

g2o is an open-source C++ framework for optimizing graph-based nonlinear error
functions. g2o has been designed to be easily extensible to a wide range of
problems and a new problem typically can be specified in a few lines of code.
The current implementation provides solutions to several variants of SLAM and
BA.

A wide range of problems in robotics as well as in computer-vision involve the
minimization of a non-linear error function that can be represented as a graph.
Typical instances are simultaneous localization and mapping (SLAM) or bundle
adjustment (BA). The overall goal in these problems is to find the
configuration of parameters or state variables that maximally explain a set of
measurements affected by Gaussian noise. g2o is an open-source C++ framework
for such nonlinear least squares problems. g2o has been designed to be easily
extensible to a wide range of problems and a new problem typically can be
specified in a few lines of code. The current implementation provides solutions
to several variants of SLAM and BA. g2o offers a performance comparable to
implementations of state-of-the-art approaches for the specific problems
(02/2011).
### Requirements
g2o requires cmake and Eigen3 to build. The other requirements are optional.
  * cmake             http://www.cmake.org/
  * Eigen3            http://eigen.tuxfamily.org
  * suitesparse       http://www.cise.ufl.edu/research/sparse/SuiteSparse/
  * Qt5               http://qt-project.org
  * libQGLViewer      http://www.libqglviewer.com/

  On Ubuntu / Debian these dependencies are resolved by installing the
  following packages.
    - cmake
    - libeigen3-dev
    - libsuitesparse-dev
    - Qt4: `libqt4-dev`, `qt4-qmake`, `libqglviewer-dev` (Or `libqglviewer-qt4-dev` in modern distributions)
    - Qt5: `libqt5-dev`, `qt5-qmake`, `libqglviewer-dev`
### Compilation
Our primary development platform is Linux. We recommend a so-called out of source build which can be achieved
by the following command sequence.

        - `mkdir build`
        - `cd build`
        - `cmake ../`
        - `make`
        - `make install`

Don't forget to add the following command in your CMakeLists.txt.
> list( APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules )