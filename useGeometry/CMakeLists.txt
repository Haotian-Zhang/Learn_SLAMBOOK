cmake_minimum_required(VERSION 3.10)
project(useGeometry)

#set(CMAKE_CXX_STANDARD 11)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS "-o3")

add_executable(useGeometry useGeometry.cpp)

include_directories("/usr/include/eigen3")