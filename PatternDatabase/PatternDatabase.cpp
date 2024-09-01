
#include "PatternDatabase.h"
#include <bits/stdc++.h>
using namespace std;

PatternDatabase::PatternDatabase(uint32_t _size, uint8_t init_value = 0) : database(_size, init_value), size(_size), numOfItems(0) {}

void PatternDatabase::setNumOfMoves(const RubiksCube &cube, uint8_t value)
{
    uint32_t index = getCubeIndex(cube);
    database.set(index, value);
}

uint32_t PatternDatabase::getNumOfMoves(const RubiksCube &cube)
{
    uint32_t index = getCubeIndex(cube);
    return database.get(index);
}

bool PatternDatabase::writeToFile(string filePath) const
{
    ofstream outFile(filePath, ios::binary);

    if (!outFile)
    {
        cerr << "Error Opening the file\n";
        cerr << "Reason: " << strerror(errno) << endl;
        return false;
    }

    outFile.write(reinterpret_cast<const char *>(database.getData()), database.getSize());

    if (!outFile)
    {
        cerr << "Failed to write data to file " << filePath << '\n';
        cerr << "Reason: " << strerror(errno) << endl;
        return false;
    }

    outFile.close();

    return true;
}

bool PatternDatabase::getFromFile(string filePath)
{
    ifstream inFile(filePath, ios::binary);

    if (!inFile)
    {
        cerr << "Failed to read from file " << filePath << '\n';
        cerr << "Reason: " << strerror(errno) << endl;
        return false;
    }

    inFile.seekg(0, ios::end);
    uint32_t dataSize = inFile.tellg();
    inFile.seekg(0, ios::beg);

    if (dataSize != database.getSize())
    {
        cerr << "File data size does not match \n";
        cerr << "Reason: " << strerror(errno) << endl;
        return false;
    }

    inFile.read(reinterpret_cast<char *>(database.getData()), dataSize);

    if (!inFile)
    {
        cerr << "Failed when copying data to database\n";
        cerr << "Reason: " << strerror(errno) << endl;
        return false;
    }

    inFile.close();

    return true;
}
