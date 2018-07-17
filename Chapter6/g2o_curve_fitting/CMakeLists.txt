cmake_minimum_required(VERSION 3.10)
project(g2o_curve_fitting)

set( CMAKE_BUILD_TYPE "Release" )
set( CMAKE_CXX_FLAGS "-std=c++11 -O3" )

list( APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules )

# 寻找G2O
find_package( G2O REQUIRED )
include_directories(
        ${G2O_INCLUDE_DIRS}
        "/usr/include/eigen3"
)

# OpenCV
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_DIRS} )

add_executable(g2o_curve_fitting g2o_curve_fitting.cpp)

target_link_libraries( g2o_curve_fitting
        ${OpenCV_LIBS}
        g2o_core g2o_stuff
        )