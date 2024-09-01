#include <bits/stdc++.h>
#include "../Models/RubiksCube.h"

#ifndef RUBIKS_CUBE_SOLVER_DFSSOLVER_H
#define RUBIKS_CUBE_SOLVER_DFSSOLVER_H

// Typename T: rubiks cube model used (3d, 1d, bitBoard)
// Typename H: corresponding hash function

template <typename T, typename H>
class DFSSolver
{
private:
    vector<RubiksCube::MOVE> moves;
    unordered_map<T, bool, H> visited;
    int max_search_depth;
    bool dfs(int depth)
    {
        if (rubiksCube.isSolved())
            return true;

        if (depth > max_search_depth || visited[rubiksCube])
            return false;

        for (int moveIndx = 0; moveIndx < 18; moveIndx++)
        {
            // performing the move
            rubiksCube.move(RubiksCube::MOVE(moveIndx));
            // storing the move in moves array
            moves.push_back(RubiksCube::MOVE(moveIndx));
            // calling dfs for next level
            if (dfs(depth + 1))
                return true;
            // current move doesn't lead to valid solution so pop it out and try next move
            moves.pop_back();
            // inverting the move performed on cube
            rubiksCube.invert(RubiksCube::MOVE(moveIndx));
        }
        // if none of the moves worked then returned false
        return false;
    }

public:
    T rubiksCube;

    DFSSolver(T _rubiksCube, int _max_search_depth)
    {
        rubiksCube = _rubiksCube;
        max_search_depth = _max_search_depth;
    }

    vector<RubiksCube::MOVE> solve()
    {
        dfs(0);
        return moves;
    }
};

#endif // RUBIKS_CUBE_SOLVER_DFSSOLVER_H