cmake_minimum_required(VERSION 3.10)
project(EIgen)

set( CMAKE_BUILD_TYPE "Release" )
set( CMAKE_CXX_FLAGS "-O3" )

add_executable(EIgen useEigen.cpp)

include_directories("/usr/include/eigen3")