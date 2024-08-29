#include "Models/RubiksCube3dArray.cpp"
#include <bits/stdc++.h>
using namespace std;

signed main()
{
    RubiksCube3dArray cube;
    cube.print();
    cube.move(RubiksCube::MOVE::L);
    cube.print();
    cube.invert(RubiksCube::MOVE::L);
    cube.print();
    cube.randomShuffle(5);
    cube.print();
    return 0;
}