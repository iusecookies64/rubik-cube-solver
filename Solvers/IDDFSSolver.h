#include <bits/stdc++.h>
#include "../Models/RubiksCube.h"
#include "DFSSolver.h"

#ifndef RUBIKS_CUBE_SOLVER_IDDFSSOLVER_H
#define RUBIKS_CUBE_SOLVER_IDDFSSOLVER_H

template <typename T, typename H>
class IDDFSSolver
{
private:
    int max_search_depth;
    vector<RubiksCube::MOVE> moves;

public:
    T rubiksCube;
    IDDFSSolver(T _rubiksCube, int _max_search_depth)
    {
        rubiksCube = _rubiksCube;
        max_search_depth = _max_search_depth;
    }

    vector<RubiksCube::MOVE> solve()
    {
        for (int depth = 1; depth <= max_search_depth; depth++)
        {
            DFSSolver<T, H> solver(rubiksCube);
            moves = solver.solve();
            if (solver.rubiksCube.isSolved())
            {
                // if cube solved, assign solved cube to current cube
                rubiksCube = solver.rubiksCube;
                break;
            }
        }
        return moves;
    }
};

#endif // RUBIKS_CUBE_SOLVER_IDDFSSOLVER_H