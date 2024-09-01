
#ifndef RUBIKS_CUBE_SOLVER_IDASTARSOLVER_H
#define RUBIKS_CUBE_SOLVER_IDASTARSOLVER_H

#include "../Models/RubiksCube.h"
#include "../PatternDatabase/CornerPatternDatabase.cpp"
#include <bits/stdc++.h>
using namespace std;

template <typename T, typename H>
class IDAStarSolver
{
private:
    uint32_t max_depth;
    unordered_map<T, RubiksCube::MOVE, H> move_done;
    unordered_map<T, bool, H> visited;
    CornerPatternDatabase patternDb;

    void resetStructure()
    {
        visited.clear();
        move_done.clear();
    }

    struct Node
    {
        T cube;
        uint32_t depth;
        uint32_t estimate;

        Node(T _cube, uint32_t _depth, uint32_t _estimate) : cube(_cube), depth(_depth), estimate(_estimate) {};
    };

    struct compare
    {
        bool operator()(pair<Node, uint32_t> const &p1, pair<Node, uint32_t> const &p2)
        {
            const Node &n1 = p1.first, &n2 = p2.first;
            if (n1.depth + n1.estimate == n2.depth + n2.estimate)
            {
                return (n1.estimate > n2.estimate);
            }
            else
            {
                return n1.depth + n1.estimate > n2.depth + n2.estimate;
            }
        }
    };

    uint32_t IDAStar(uint32_t bound)
    {
        priority_queue<pair<Node, uint32_t>, vector<pair<Node, uint32_t>>, compare> pq;
        auto start = make_pair(Node(rubiksCube, 0, patternDb.getNumOfMoves(rubiksCube)), 0);
        pq.push(start);
        uint32_t next_bound = 100;
        while (!pq.empty())
        {
            Node node = pq.top().first;
            uint32_t moveDone = pq.top().second;
            pq.pop();
            if (visited[node.cube])
                continue;

            visited[node.cube] = true;
            move_done[node.cube] = RubiksCube::MOVE(moveDone);
            node.depth++;

            if (node.cube.isSolved())
                return bound;

            for (int indx = 0; indx < 18; indx++)
            {
                node.cube.move(RubiksCube::MOVE(indx));
                if (!visited[node.cube])
                {
                    node.estimate = patternDb.getNumOfMoves(node.cube);
                    if (node.estimate + node.depth > bound)
                    {
                        next_bound = min(next_bound, node.estimate + node.depth);
                    }
                    else
                    {
                        pq.push(make_pair(node, indx));
                    }
                }
                node.cube.invert(RubiksCube::MOVE(indx));
            }
        }
        return next_bound;
    }

public:
    T rubiksCube;
    IDAStarSolver(T _rubiksCube, uint32_t _max_depth) : patternDb()
    {
        rubiksCube = _rubiksCube;
        max_depth = _max_depth;
        patternDb.getFromFile("Database/cornerPatternDb.txt");
    }

    vector<RubiksCube::MOVE> solve()
    {
        int curr_bound = 1;
        bool found = false;
        vector<RubiksCube::MOVE> moves;

        while (curr_bound <= max_depth)
        {
            uint32_t next_bound = IDAStar(curr_bound);
            if (next_bound == curr_bound)
            {
                // answer found
                found = true;
                break;
            }
            curr_bound = next_bound;
            resetStructure();
        }
        if (found)
        {
            T curr_cube;
            while (!(curr_cube == rubiksCube))
            {
                moves.push_back(move_done[curr_cube]);
                curr_cube.invert(moves.back());
            }
            reverse(moves.begin(), moves.end());
        }
        else
        {
            cout << "could not solve\n";
        }

        return moves;
    }
};

#endif // RUBIKS_CUBE_SOLVER_IDASTARSOLVER_H