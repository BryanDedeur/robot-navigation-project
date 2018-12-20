cmake_minimum_required(VERSION 3.12)
project(BonusProject)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin)

add_executable(BonusProject main.cpp MapNode.cpp MapNode.h VectorMap.cpp VectorMap.h)