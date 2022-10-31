cmake_minimum_required(VERSION 3.10)

set(TARGET HPC_Tutor)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

# TODO: temporal solution, we have to remove the trash.cpp file
add_library(${TARGET} STATIC Matrix.hpp MatrixView.hpp trash.cpp)
