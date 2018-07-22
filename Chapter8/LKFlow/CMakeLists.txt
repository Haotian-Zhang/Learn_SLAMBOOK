cmake_minimum_required(VERSION 3.10)
project(LKFlow)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_LIBS})

include_directories("/usr/include/eigen3")

add_executable(LKFlow useLK.cpp)
target_link_libraries(LKFlow ${OpenCV_LIBS})