cmake_minimum_required(VERSION 3.10)
project(useSophus)

#set(CMAKE_CXX_STANDARD 11)

find_package( Sophus REQUIRED)

include_directories( ${Sophus_INCLUDE_DIRS} )
#include_directories("/usr/include/eigen3")

add_executable(useSophus useSophus.cpp)
target_link_libraries( useSophus ${Sophus_LIBRARIES})

