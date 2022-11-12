cmake_minimum_required(VERSION 3.23)
project(math_matrix_hw_3)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(math_matrix_hw_3
        main.cpp
        matrix.cpp
        matrix.h
        kramer.cpp
        kramer.h)


