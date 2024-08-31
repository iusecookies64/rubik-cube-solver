
#include <bits/stdc++.h>
#include "../Models/RubiksCube.h"

#ifndef RUBIKS_CUBE_SOLVER_BFSSOLVER_H
#define RUBIKS_CUBE_SOLVER_BFSSOLVER_H

// Typename T: rubiks cube model used (3d, 1d, bitBoard)
// Typename H: corresponding hash function

template <typename T, typename H>
class BFSSolver
{
private:
    int max_search_depth;
    // to store visited states
    unordered_map<T, int, H> visited;
    // to store for each state, what move was done to reach it (for answer generation)
    unordered_map<T, RubiksCube::MOVE, H> move_done;

    bool bfs()
    {
        queue<T> q;
        q.push(rubiksCube);
        visited[rubiksCube] = 1; // depth 1
        while (!q.empty())
        {
            T node = q.front();
            q.pop();
            int currentDepth = visited[node];
            if (currentDepth == max_search_depth)
            {
                return false; // could not solve cube for given depth
            }
            for (int moveIndex = 0; moveIndex < 18; moveIndex++)
            {
                node.move(RubiksCube::MOVE(moveIndex));
                if (!visited[node])
                {
                    visited[node] = currentDepth + 1;
                    move_done[node] = RubiksCube::MOVE(moveIndex);
                    if (node.isSolved())
                        return true;
                    q.push(node);
                }
                node.invert(RubiksCube::MOVE(moveIndex));
            }
        }
        return false;
    }

public:
    T rubiksCube;
    BFSSolver(T _rubiksCube, int _max_search_depth)
    {
        rubiksCube = _rubiksCube;
        max_search_depth = _max_search_depth;
    }

    vector<RubiksCube::MOVE> solve()
    {
        vector<RubiksCube::MOVE> moves;
        // if already solved we return empty moves
        if (rubiksCube.isSolved())
            return moves;

        // solving via bfs
        bool solved = bfs();
        // if not able to solve return empty moves
        if (!solved)
            return moves;

        T curr_cube; // initializes a solved cube, and we back track from solved cube to initial cube
        do
        {
            // pushing the move performed to reach this node into moves
            moves.push_back(move_done[curr_cube]);
            // inverting the move to get previous state
            curr_cube.invert(moves.back());
        } while (!(curr_cube == rubiksCube));

        reverse(moves.begin(), moves.end());
        return moves;
    }
};

#endif // RUBIKS_CUBE_SOLVER_BFSSOLVER_H