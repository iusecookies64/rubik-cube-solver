
#ifndef RUBIKS_CUBE_PATTER_DATABASE_H
#define RUBIKS_CUBE_PATTER_DATABASE_H

#include <bits/stdc++.h>
#include "../Utils/NibbleArray.h"
#include "../Models/RubiksCube.h"
#include "../Utils/PermutationIndexer.h"

class PatternDatabase
{
private:
    NibbleArray database;
    uint32_t size;
    uint32_t numOfItems;

public:
    PatternDatabase(uint32_t _size, uint8_t init_value);

    virtual uint32_t getCubeIndex(const RubiksCube &cube) = 0;

    void setNumOfMoves(const RubiksCube &cube, uint8_t value);

    uint32_t getNumOfMoves(const RubiksCube &cube);

    bool writeToFile(string filePath) const;

    bool getFromFile(string filePath);
};

#endif // RUBIKS_CUBE_PATTER_DATABASE_H