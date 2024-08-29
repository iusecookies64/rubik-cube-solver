#include "Models/RubiksCubeBitBoard.cpp"
#include <bits/stdc++.h>
using namespace std;

signed main()
{
    RubiksCubeBitBoard cube;
    cube.print();
    cube.move(RubiksCube::MOVE::L);
    cube.print();
    cube.move(RubiksCube::MOVE::F);
    cube.print();
    return 0;
}