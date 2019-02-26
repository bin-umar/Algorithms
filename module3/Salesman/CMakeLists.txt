cmake_minimum_required(VERSION 3.13)
project(Salesman)

set(CMAKE_CXX_STANDARD 14)

add_executable(Salesman main.cpp include/checker.h src/checker.cpp include/dots.h
        include/graph.h include/MST.h include/TSP_BF.h include/TSP_BF.h src/dots.cpp src/graph.cpp src/graph.cpp
        src/MST.cpp src/TSP_BF.cpp src/TSP_MST.cpp)