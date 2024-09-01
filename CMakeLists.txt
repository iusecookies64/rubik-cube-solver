cmake_minimum_required(VERSION 3.0.0)

project(RubiksCubeSolver)

add_executable(${PROJECT_NAME} Models/RubiksCube.h Models/RubiksCube.cpp Models/RubiksCube3dArray.cpp Solvers/DFSSolver.h Solvers/BFSSolver.h Solvers/IDDFSSolver.h Solvers/IDAStarSolver.h PatternDatabase/PatternDatabase.h PatternDatabase/PatternDatabase.cpp PatternDatabase/CornerPatternDatabase.cpp PatternDatabase/CornerDBMaker.h Utils/NibbleArray.h Utils/NibbleArray.cpp Utils/PermutationIndexer.h main.cpp)