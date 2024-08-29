cmake_minimum_required(VERSION 3.0.0)

project(RubiksCubeSolver)

add_executable(${PROJECT_NAME} Models/RubiksCube.h Models/RubiksCube.cpp Models/RubiksCube3dArray.cpp main.cpp)