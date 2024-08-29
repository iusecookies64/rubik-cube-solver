#include "RubiksCube.h"

class RubiksCubeBitBoard : public RubiksCube
{
    uint64_t solved_side_config[6];

    int arr[3][3] = {{0, 1, 2},
                     {7, 8, 3},
                     {6, 5, 4}};

    uint64_t one_8 = (1 << 8) - 1, one_24 = (1 << 24) - 1;

    void rotateFace(FACE face)
    {
        int faceIndex = int(face);
        uint64_t side = bitBoard[faceIndex];
        uint64_t last2ColorsMask = (side >> (8 * 6));
        bitBoard[faceIndex] = (side << (8 * 2)) | last2ColorsMask;
    }

    // change colors of cells c11, c12, c13 on face1 to colors of cells c21, c22, c23 on face2 correspondingly
    void rotateSide(FACE face1, int c11, int c12, int c13, FACE face2, int c21, int c22, int c23)
    {
        uint64_t color1 = (bitBoard[int(face2)] & (one_8 << (8 * c21))) >> (8 * c21);
        uint64_t color2 = (bitBoard[int(face2)] & (one_8 << (8 * c22))) >> (8 * c22);
        uint64_t color3 = (bitBoard[int(face2)] & (one_8 << (8 * c23))) >> (8 * c23);

        bitBoard[int(face1)] = (bitBoard[int(face1)] & ~(one_8 << (8 * c11))) | (color1 << (8 * c11));
        bitBoard[int(face1)] = (bitBoard[int(face1)] & ~(one_8 << (8 * c12))) | (color2 << (8 * c12));
        bitBoard[int(face1)] = (bitBoard[int(face1)] & ~(one_8 << (8 * c13))) | (color3 << (8 * c13));
    }
    // adds color to cell of face
    void addColor(FACE face, int cell, int color)
    {
        bitBoard[int(face)] = (bitBoard[int(face)] & ~(one_8 << (8 * cell))) | (color << (8 * cell));
    }

    uint64_t getColorMask(FACE face, unsigned int cellIndex) const
    {
        uint64_t color = (bitBoard[int(face)] & (one_8 << (8 * cellIndex))) >> (8 * cellIndex);
        return color;
    }

public:
    uint64_t bitBoard[6]{};
    RubiksCubeBitBoard()
    {
        for (int side = 0; side < 6; side++)
        {
            uint64_t color = (1 << side);
            for (int cellIndex = 0; cellIndex < 8; cellIndex++)
            {
                bitBoard[side] |= (color << (8 * cellIndex));
            }
            solved_side_config[side] = bitBoard[side];
        }
    }

    COLOR getColor(FACE face, unsigned int row, unsigned int col) const override
    {
        // getting the index or (row, col) in bit representation
        int cellIndex = arr[row][col];
        if (cellIndex == 8)
            return COLOR(int(face));

        uint64_t side = bitBoard[int(face)];
        uint64_t cellMask = ((side >> (8 * cellIndex)) & one_8);

        // finding color Index
        int colorIndex = 0;
        for (int i = 0; i < 8; i++)
        {
            if (cellMask & (1 << i))
            {
                colorIndex = i;
                break;
            }
        }

        return COLOR(colorIndex);
    }

    bool isSolved() const override
    {
        for (int i = 0; i < 6; i++)
        {
            if (bitBoard[i] != solved_side_config[i])
                return false;
        }
        return true;
    }

    RubiksCube &u() override
    {
        rotateFace(FACE::UP);
        // getting colors of top row in front face
        uint64_t color1 = getColorMask(FACE::FRONT, 0);
        uint64_t color2 = getColorMask(FACE::FRONT, 1);
        uint64_t color3 = getColorMask(FACE::FRONT, 2);

        rotateSide(FACE::FRONT, 0, 1, 2, FACE::RIGHT, 0, 1, 2);
        rotateSide(FACE::RIGHT, 0, 1, 2, FACE::BACK, 0, 1, 2);
        rotateSide(FACE::BACK, 0, 1, 2, FACE::LEFT, 0, 1, 2);

        // adding colors of front row to left row
        addColor(FACE::LEFT, 0, color1);
        addColor(FACE::LEFT, 1, color2);
        addColor(FACE::LEFT, 2, color3);

        return *this;
    }

    RubiksCube &d() override
    {
        rotateFace(FACE::DOWN);
        // storing bottom row of front face colors
        uint64_t color1 = getColorMask(FACE::FRONT, 6);
        uint64_t color2 = getColorMask(FACE::FRONT, 5);
        uint64_t color3 = getColorMask(FACE::FRONT, 4);

        rotateSide(FACE::FRONT, 6, 5, 4, FACE::LEFT, 6, 5, 4);
        rotateSide(FACE::LEFT, 6, 5, 4, FACE::BACK, 6, 5, 4);
        rotateSide(FACE::BACK, 6, 5, 4, FACE::RIGHT, 6, 5, 4);

        addColor(FACE::RIGHT, 6, color1);
        addColor(FACE::RIGHT, 5, color2);
        addColor(FACE::RIGHT, 4, color3);

        return *this;
    }

    RubiksCube &l() override
    {
        rotateFace(FACE::LEFT);

        uint64_t color1 = getColorMask(FACE::FRONT, 0);
        uint64_t color2 = getColorMask(FACE::FRONT, 7);
        uint64_t color3 = getColorMask(FACE::FRONT, 6);

        rotateSide(FACE::FRONT, 0, 7, 6, FACE::UP, 0, 7, 6);
        rotateSide(FACE::UP, 0, 7, 6, FACE::BACK, 4, 3, 2);
        rotateSide(FACE::BACK, 4, 3, 2, FACE::DOWN, 0, 7, 6);

        addColor(FACE::DOWN, 0, color1);
        addColor(FACE::DOWN, 7, color2);
        addColor(FACE::DOWN, 6, color3);

        return *this;
    }

    RubiksCube &r() override
    {
        rotateFace(FACE::RIGHT);

        uint64_t color1 = getColorMask(FACE::FRONT, 2);
        uint64_t color2 = getColorMask(FACE::FRONT, 3);
        uint64_t color3 = getColorMask(FACE::FRONT, 4);

        rotateSide(FACE::FRONT, 2, 3, 4, FACE::DOWN, 2, 3, 4);
        rotateSide(FACE::DOWN, 2, 3, 4, FACE::BACK, 6, 7, 0);
        rotateSide(FACE::BACK, 6, 7, 0, FACE::UP, 2, 3, 4);

        addColor(FACE::RIGHT, 2, color1);
        addColor(FACE::RIGHT, 3, color2);
        addColor(FACE::RIGHT, 4, color3);

        return *this;
    }

    RubiksCube &f() override
    {
        rotateFace(FACE::FRONT);

        uint64_t color1 = getColorMask(FACE::UP, 6);
        uint64_t color2 = getColorMask(FACE::UP, 5);
        uint64_t color3 = getColorMask(FACE::UP, 4);

        rotateSide(FACE::UP, 6, 5, 4, FACE::LEFT, 4, 3, 2);
        rotateSide(FACE::LEFT, 4, 3, 2, FACE::DOWN, 2, 1, 0);
        rotateSide(FACE::DOWN, 2, 1, 0, FACE::RIGHT, 0, 7, 6);

        addColor(FACE::RIGHT, 0, color1);
        addColor(FACE::RIGHT, 7, color2);
        addColor(FACE::RIGHT, 6, color3);

        return *this;
    }

    RubiksCube &b() override
    {
        rotateFace(FACE::BACK);

        uint64_t color1 = getColorMask(FACE::UP, 0);
        uint64_t color2 = getColorMask(FACE::UP, 1);
        uint64_t color3 = getColorMask(FACE::UP, 2);

        rotateSide(FACE::UP, 0, 1, 2, FACE::RIGHT, 2, 3, 4);
        rotateSide(FACE::RIGHT, 2, 3, 4, FACE::DOWN, 6, 5, 4);
        rotateSide(FACE::DOWN, 6, 5, 4, FACE::LEFT, 0, 7, 6);

        addColor(FACE::LEFT, 6, color1);
        addColor(FACE::LEFT, 7, color2);
        addColor(FACE::LEFT, 0, color3);

        return *this;
    }

    RubiksCubeBitBoard &operator=(RubiksCubeBitBoard &rt)
    {
        for (int i = 0; i < 6; i++)
        {
            bitBoard[i] = rt.bitBoard[i];
        }

        return *this;
    }

    bool operator==(RubiksCubeBitBoard &rt)
    {
        for (int i = 0; i < 6; i++)
        {
            if (bitBoard[i] != rt.bitBoard[i])
                return false;
        }
        return true;
    }
};

struct Hash1dModel
{
    size_t operator()(const RubiksCubeBitBoard &rt) const
    {
        uint64_t hash = 0;
        for (int i = 0; i < 54; i++)
        {
            hash ^= rt.bitBoard[i];
        }
        return (size_t)hash;
    }
};