cmake_minimum_required(VERSION 3.12)
project(Algorithms)

set(CMAKE_CXX_STANDARD 14)
add_executable(Algorithms main.cpp module3/task1/CListGraph.cpp module3/task1/CMatrixGraph.cpp module3/task1/CSetGraph.cpp module3/task1/CArcGraph.cpp)
