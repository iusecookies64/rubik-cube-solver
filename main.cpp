#include "Models/RubiksCube.h"
#include "Models/RubiksCubeBitBoard.cpp"
#include "Models/RubiksCube3dArray.cpp"
#include "Models/RubiksCube1dArray.cpp"
#include "Solvers/DFSSolver.h"
#include "Solvers/BFSSolver.h"
#include "Solvers/IDDFSSolver.h"
// #include "Solvers/IDAStarSolver.h"
#include "PatternDatabase/CornerPatternDatabase.cpp"
#include <bits/stdc++.h>
using namespace std;

template <template <typename, typename> class S>
void TestSolveSpeed(vector<RubiksCube::MOVE> &moves)
{
    int depth = moves.size();

    RubiksCube1dArray cube1;
    RubiksCube3dArray cube2;
    RubiksCubeBitBoard cube3;

    // applying the same moves of other cubes as well
    for (auto move : moves)
    {
        cube1.move(move);
        cube2.move(move);
        cube3.move(move);
    }

    S<RubiksCube1dArray, Hash1dModel> solver1(cube1, depth);
    S<RubiksCube3dArray, Hash3dModel> solver2(cube2, depth);
    S<RubiksCubeBitBoard, HashBitBoard> solver3(cube3, depth);

    string models[] = {"1d Model", "3d Model", "Bitboard Model"};
    for (int i = 0; i < 3; i++)
    {
        auto start = chrono::high_resolution_clock::now();
        if (i == 0)
            solver1.solve();
        else if (i == 1)
            solver2.solve();
        else
            solver3.solve();
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> duration = end - start;
        cout << models[i] << " solved in " << duration.count() / 1000 << "s\n";
    }
}

signed main()
{
    uint32_t depth = 500;
    RubiksCubeBitBoard cube;
    vector<RubiksCube::MOVE> moves = cube.randomShuffle(depth);
    cube.print();

    // only run there algos for small depths
    if (depth <= 7)
    {
        cout << "\nTimes for dfs solver\n";
        TestSolveSpeed<DFSSolver>(moves);

        cout << "\nTimes for bfs solver\n";
        TestSolveSpeed<BFSSolver>(moves);

        cout << "\nTimes for iddfs solver\n";
        TestSolveSpeed<BFSSolver>(moves);
    }

    // cout << "\nTime for idastar solver\n";
    // TestSolveSpeed<IDAStarSolver>(moves);

    CornerPatternDatabase db;
    db.getFromFile("Database/cornerPatternDb.txt");
    cout << db.getNumOfMoves(cube) << endl;

    return 0;
}
