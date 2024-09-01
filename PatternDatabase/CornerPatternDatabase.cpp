
#include "PatternDatabase.h"
#include "../Utils/PermutationIndexer.h"
#include "../Models/RubiksCube.h"
#include <bits/stdc++.h>

class CornerPatternDatabase : public PatternDatabase
{
private:
    PermutationIndexer<8> indexer;

public:
    // initializing database size as (7! + 6! + ... + 1!) * 2187 = 1312200 which is highest index of a permutation
    CornerPatternDatabase(int8_t init_value = 0) : PatternDatabase(13122000, init_value) {}

    uint32_t getCubeIndex(const RubiksCube &cube) override
    {
        vector<uint32_t> perm = {
            cube.getCornerIndex(0),
            cube.getCornerIndex(1),
            cube.getCornerIndex(2),
            cube.getCornerIndex(3),
            cube.getCornerIndex(4),
            cube.getCornerIndex(5),
            cube.getCornerIndex(6),
        };

        uint32_t permRank = indexer.getPermutationIndex(perm);

        // calculating orientation value
        // each orientation can be represented as a unique number in base 3 numbers
        // total 7 paces are there hence orientationRank < 3^7 = 2187
        uint32_t orientationRank = cube.getCornerOrientation(0) * 729 +
                                   cube.getCornerOrientation(1) * 243 +
                                   cube.getCornerOrientation(2) * 81 +
                                   cube.getCornerOrientation(3) * 27 +
                                   cube.getCornerOrientation(4) * 9 +
                                   cube.getCornerOrientation(5) * 3 +
                                   cube.getCornerOrientation(6);

        return permRank * 2187 + orientationRank;
    }
};