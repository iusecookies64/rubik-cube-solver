
#include "RubiksCube.h"

class RubiksCube1dArray : public RubiksCube
{
private:
    // returns the index in flatten for given (face, row, col)
    static inline int getIndex(FACE face, int row, int col)
    {
        return 9 * int(face) + 3 * row + col;
    }
    // perform clockwise rotation on face
    void rotateFace(FACE face)
    {
        char currFace[3][3];
        // copying curr face into currFace array
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                currFace[i][j] = cube[getIndex(face, i, j)];
            }
        }

        // updating the curr face row 0
        for (int i = 0; i < 3; i++)
            cube[getIndex(face, 0, i)] = currFace[2 - i][0];
        // updating the curr face row 2
        for (int i = 0; i < 3; i++)
            cube[getIndex(face, 2, i)] = currFace[2 - i][2];
        // updating the curr face col 0
        for (int i = 0; i < 3; i++)
            cube[getIndex(face, i, 0)] = currFace[2][i];
        // updating the curr face col 2
        for (int i = 0; i < 3; i++)
            cube[getIndex(face, i, 2)] = currFace[0][i];
    }

public:
    char cube[54];
    RubiksCube1dArray()
    {
        // initializing a solved cube
        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    cube[getIndex(FACE(i), j, k)] = getColorLetter(COLOR(i));
                }
            }
        }
    }

    COLOR getColor(FACE face, unsigned int row, unsigned int col) const override
    {
        char colorChar = cube[getIndex(face, row, col)];
        return getColorFromChar(colorChar);
    }

    bool isSolved() const override
    {
        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    if (cube[getIndex(FACE(i), j, k)] != getColorLetter(COLOR(i)))
                        return false;
                }
            }
        }
        return true;
    }

    RubiksCube &u() override
    {
        rotateFace(FACE::UP);
        // storing front top row in separate array
        char temp[3];
        for (int i = 0; i < 3; i++)
            temp[i] = cube[getIndex(FACE::FRONT, 0, i)];
        for (int i = 0; i < 3; i++)
            cube[getIndex(FACE::FRONT, 0, i)] = cube[getIndex(FACE::RIGHT, 0, i)];
        for (int i = 0; i < 3; i++)
            cube[getIndex(FACE::RIGHT, 0, i)] = cube[getIndex(FACE::BACK, 0, i)];
        for (int i = 0; i < 3; i++)
            cube[getIndex(FACE::BACK, 0, i)] = cube[getIndex(FACE::LEFT, 0, i)];
        for (int i = 0; i < 3; i++)
            cube[getIndex(FACE::LEFT, 0, i)] = temp[i];

        return *this;
    }

    RubiksCube &d()
    {
        rotateFace(FACE::DOWN);

        char temp[3];
        for (int i = 0; i < 3; i++)
            temp[i] = cube[getIndex(FACE::FRONT, 2, i)];

        for (int i = 0; i < 3; i++)
            cube[getIndex(FACE::FRONT, 2, i)] = cube[getIndex(FACE::LEFT, 2, i)];
        for (int i = 0; i < 3; i++)
            cube[getIndex(FACE::LEFT, 2, i)] = cube[getIndex(FACE::BACK, 2, i)];
        for (int i = 0; i < 3; i++)
            cube[getIndex(FACE::BACK, 2, i)] = cube[getIndex(FACE::RIGHT, 2, i)];
        for (int i = 0; i < 3; i++)
            cube[getIndex(FACE::RIGHT, 2, i)] = temp[i];

        return *this;
    }

    RubiksCube &l() override
    {
        rotateFace(FACE::LEFT);

        char temp[3];
        for (int i = 0; i < 3; i++)
            temp[i] = cube[getIndex(FACE::FRONT, i, 0)];

        for (int i = 0; i < 3; i++)
            cube[getIndex(FACE::FRONT, i, 0)] = cube[getIndex(FACE::UP, i, 0)];
        for (int i = 0; i < 3; i++)
            cube[getIndex(FACE::UP, i, 0)] = cube[getIndex(FACE::BACK, 2 - i, 2)];
        for (int i = 0; i < 3; i++)
            cube[getIndex(FACE::BACK, 2 - i, 2)] = cube[getIndex(FACE::DOWN, i, 0)];
        for (int i = 0; i < 3; i++)
            cube[getIndex(FACE::DOWN, i, 0)] = temp[i];

        return *this;
    }

    RubiksCube &r() override
    {
        rotateFace(FACE::RIGHT);

        char temp[3];
        for (int i = 0; i < 3; i++)
            temp[i] = cube[getIndex(FACE::FRONT, i, 2)];

        for (int i = 0; i < 3; i++)
            cube[getIndex(FACE::FRONT, i, 2)] = cube[getIndex(FACE::DOWN, i, 2)];
        for (int i = 0; i < 3; i++)
            cube[getIndex(FACE::DOWN, i, 2)] = cube[getIndex(FACE::BACK, 2 - i, 0)];
        for (int i = 0; i < 3; i++)
            cube[getIndex(FACE::BACK, 2 - i, 0)] = cube[getIndex(FACE::UP, i, 2)];
        for (int i = 0; i < 3; i++)
            cube[getIndex(FACE::UP, i, 2)] = temp[i];

        return *this;
    }

    RubiksCube &f() override
    {
        rotateFace(FACE::FRONT);

        char temp[3];
        for (int i = 0; i < 3; i++)
            temp[i] = cube[getIndex(FACE::UP, 2, i)];

        for (int i = 0; i < 3; i++)
            cube[getIndex(FACE::UP, 2, i)] = cube[getIndex(FACE::LEFT, 2 - i, 2)];
        for (int i = 0; i < 3; i++)
            cube[getIndex(FACE::LEFT, 2 - i, 2)] = cube[getIndex(FACE::DOWN, 0, 2 - i)];
        for (int i = 0; i < 3; i++)
            cube[getIndex(FACE::DOWN, 0, 2 - i)] = cube[getIndex(FACE::RIGHT, i, 0)];
        for (int i = 0; i < 3; i++)
            cube[getIndex(FACE::RIGHT, i, 0)] = temp[i];

        return *this;
    }

    RubiksCube &b() override
    {
        rotateFace(FACE::BACK);

        char temp[3];
        for (int i = 0; i < 3; i++)
            temp[i] = cube[getIndex(FACE::UP, 0, i)];

        for (int i = 0; i < 3; i++)
            cube[getIndex(FACE::UP, 0, i)] = cube[getIndex(FACE::RIGHT, i, 2)];
        for (int i = 0; i < 3; i++)
            cube[getIndex(FACE::RIGHT, i, 2)] = cube[getIndex(FACE::DOWN, 2, 2 - i)];
        for (int i = 0; i < 3; i++)
            cube[getIndex(FACE::DOWN, 2, 2 - i)] = cube[getIndex(FACE::LEFT, 2 - i, 0)];
        for (int i = 0; i < 3; i++)
            cube[getIndex(FACE::LEFT, 2 - i, 0)] = temp[i];

        return *this;
    }

    RubiksCube1dArray &operator=(const RubiksCube1dArray &rt)
    {
        for (int i = 0; i < 54; i++)
        {
            cube[i] = rt.cube[i];
        }

        return *this;
    }

    bool operator==(const RubiksCube1dArray &rt) const
    {
        for (int i = 0; i < 54; i++)
        {
            if (cube[i] != rt.cube[i])
                return false;
        }
        return true;
    }
};

struct Hash1dModel
{
    size_t operator()(const RubiksCube1dArray &rt) const
    {
        string res = "";
        for (int i = 0; i < 54; i++)
        {
            res += rt.cube[i];
        }
        return (size_t)hash<string>()(res);
    }
};