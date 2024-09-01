#ifndef RUBIKS_CUBE_CORNER_DB_MAKE_CXX
#define RUBIKS_CUBE_CORNER_DB_MAKE_CXX

#include "CornerPatternDatabase.cpp"
#include "../Models/RubiksCube.h"
#include "../Models/RubiksCube3dArray.cpp"
#include <bits/stdc++.h>
using namespace std;

class CornerDBMaker
{
    uint32_t max_depth;

public:
    CornerDBMaker(uint32_t _max_depth)
    {
        max_depth = _max_depth;
    }

    void bfsAndStore()
    {
        // 0xff = 255 = (11111111) in binary, serves as inifite distance initializer, since max distance is 11
        CornerPatternDatabase cornerdb(0xff);
        RubiksCube3dArray cube;
        queue<RubiksCube3dArray> q;
        q.push(cube);
        int curr_depth = 0;
        while (!q.empty())
        {
            int n = q.size();
            curr_depth++;
            if (curr_depth > max_depth)
                break;
            for (int i = 0; i < n; i++)
            {
                RubiksCube3dArray node = q.front();
                q.pop();
                // performing all possible moves from this node
                for (int moveIndex = 0; moveIndex < 18; moveIndex++)
                {
                    node.move(RubiksCube::MOVE(moveIndex));
                    // checking if this node reached for first time
                    if (cornerdb.getNumOfMoves(node) > curr_depth)
                    {
                        q.push(node);
                        // storing distance as currdepth + 1
                        cornerdb.setNumOfMoves(node, curr_depth);
                    }
                    node.invert(RubiksCube::MOVE(moveIndex));
                }
            }
        }

        // after calculating all the moves we store them in file
        cornerdb.writeToFile("cornerPatternDb.txt");
        cout << "Successfully stored values in db" << endl;
    }
};
#endif // RUBIKS_CUBE_CORNER_DB_MAKE_CXX