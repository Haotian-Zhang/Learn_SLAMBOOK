cmake_minimum_required(VERSION 3.10)
project(ceres_curve_fitting)

set(CMAKE_CXX_STANDARD 11)

# 添加cmake模块已使用ceres库
list( APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules )

# 寻找Ceres库并添加他的头文件
find_package( Ceres REQUIRED)
include_directories( ${CERES_INCLUDE_DIRS} )

# OpenCV
find_package(OpenCV REQUIRED)
include_directories( ${OpenCV_DIRS} )

add_executable(ceres_curve_fitting ceres_curve_fitting.cpp)

target_link_libraries(ceres_curve_fitting ${CERES_LIBRARIES} ${OpenCV_LIBS})