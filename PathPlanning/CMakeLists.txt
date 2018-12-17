cmake_minimum_required(VERSION 3.13)
project(PathPlanning)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin)

add_executable(
        PathPlanning
        main.cpp
        PathNode.cpp
        PathNode.h
        PathList.cpp
        PathList.h
        PathMap.cpp
        PathMap.h
        MapNode.cpp
        MapNode.h VectorMap.cpp VectorMap.h)