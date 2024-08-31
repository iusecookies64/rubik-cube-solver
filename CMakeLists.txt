cmake_minimum_required(VERSION 3.0.0)

project(RubiksCubeSolver)

add_executable(${PROJECT_NAME} Models/RubiksCube.h Models/RubiksCube.cpp Models/RubiksCube3dArray.cpp Solvers/DFSSolver.h Solvers/BFSSolver.h Solvers/IDDFSSolver.h main.cpp)