cmake_minimum_required(VERSION 3.10)
project(directMethod)

set(CMAKE_CXX_STANDARD 11)

# add in CMake-Module
list( APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules )

find_package(OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS})

find_package( G2O REQUIRED)
include_directories( ${G2O_INCLUDE_DIRS} )

include_directories("/usr/include/eigen3")

set( G2O_LIBS
        g2o_core g2o_types_sba g2o_solver_csparse g2o_stuff g2o_csparse_extension
        )

add_executable(direct_sparse direct_sparse.cpp common.h)
target_link_libraries(direct_sparse ${OpenCV_LIBS} ${G2O_LIBS} )

add_executable(direct_semidense direct_semidense.cpp direct_semidense.cpp common.h)
target_link_libraries(direct_semidense ${OpenCV_LIBS} ${G2O_LIBS} )