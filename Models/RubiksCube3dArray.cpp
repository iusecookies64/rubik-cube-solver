
#include "RubiksCube.h"

class RubiksCube3dArray : public RubiksCube
{
private:
    // perform clockwise rotation on face
    void rotateFace(FACE face)
    {
        int faceIndex = int(face);
        char currFace[3][3];
        // copying curr face into currFace array
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                currFace[i][j] = cube[faceIndex][i][j];
            }
        }

        // updating the curr face row 0
        for (int i = 0; i < 3; i++)
            cube[faceIndex][0][i] = currFace[2 - i][0];
        // updating the curr face row 2
        for (int i = 0; i < 3; i++)
            cube[faceIndex][2][i] = currFace[2 - i][2];
        // updating the curr face col 0
        for (int i = 0; i < 3; i++)
            cube[faceIndex][i][0] = currFace[2][i];
        // updating the curr face col 2
        for (int i = 0; i < 3; i++)
            cube[faceIndex][i][0] = currFace[0][i];
    }

public:
    char cube[6][3][3]{};

    RubiksCube3dArray()
    {
        cout << "initializing the cube" << endl;
        // initializing a solved cube
        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    cube[i][j][k] = getColorLetter(COLOR(i));
                }
            }
        }
    }

    COLOR getColor(FACE face, unsigned int row, unsigned int col) const override
    {
        char colorChar = cube[int(face)][row][col];
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
                    if (cube[i][j][k] != getColorLetter(COLOR(i)))
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
            temp[i] = cube[int(FACE::FRONT)][0][i];
        for (int i = 0; i < 3; i++)
            cube[int(FACE::FRONT)][0][i] = cube[int(FACE::RIGHT)][0][i];
        for (int i = 0; i < 3; i++)
            cube[int(FACE::RIGHT)][0][i] = cube[int(FACE::BACK)][0][i];
        for (int i = 0; i < 3; i++)
            cube[int(FACE::BACK)][0][i] = cube[int(FACE::LEFT)][0][i];
        for (int i = 0; i < 3; i++)
            cube[int(FACE::LEFT)][0][i] = temp[i];

        return *this;
    }

    RubiksCube &uPrime() override
    {
        u();
        u();
        u();
        return *this;
    }

    RubiksCube &u2() override
    {
        u();
        u();
        return *this;
    }

    RubiksCube &d()
    {
        rotateFace(FACE::DOWN);

        char temp[3];
        for (int i = 0; i < 3; i++)
            temp[i] = cube[int(FACE::FRONT)][2][i];

        for (int i = 0; i < 3; i++)
            cube[int(FACE::FRONT)][2][i] = cube[int(FACE::LEFT)][2][i];
        for (int i = 0; i < 3; i++)
            cube[int(FACE::LEFT)][2][i] = cube[int(FACE::BACK)][2][i];
        for (int i = 0; i < 3; i++)
            cube[int(FACE::BACK)][2][i] = cube[int(FACE::RIGHT)][2][i];
        for (int i = 0; i < 3; i++)
            cube[int(FACE::RIGHT)][2][i] = temp[i];

        return *this;
    }

    RubiksCube &dPrime() override
    {
        d();
        d();
        d();
        return *this;
    }

    RubiksCube &d2() override
    {
        d();
        d();
        return *this;
    }

    RubiksCube &l() override
    {
        rotateFace(FACE::LEFT);

        char temp[3];
        for (int i = 0; i < 3; i++)
            temp[i] = cube[int(FACE::FRONT)][i][0];

        for (int i = 0; i < 3; i++)
            cube[int(FACE::FRONT)][i][0] = cube[int(FACE::UP)][i][0];
        for (int i = 0; i < 3; i++)
            cube[int(FACE::UP)][i][0] = cube[int(FACE::BACK)][2 - i][2];
        for (int i = 0; i < 3; i++)
            cube[int(FACE::BACK)][2 - i][2] = cube[int(FACE::DOWN)][i][0];
        for (int i = 0; i < 3; i++)
            cube[int(FACE::DOWN)][i][0] = temp[i];

        return *this;
    }

    RubiksCube &lPrime() override
    {
        l();
        l();
        l();
        return *this;
    }

    RubiksCube &l2() override
    {
        l();
        l();
        return *this;
    }

    RubiksCube &r() override
    {
        rotateFace(FACE::RIGHT);

        char temp[3];
        for (int i = 0; i < 3; i++)
            temp[i] = cube[int(FACE::FRONT)][i][2];

        for (int i = 0; i < 3; i++)
            cube[int(FACE::FRONT)][i][2] = cube[int(FACE::DOWN)][i][2];
        for (int i = 0; i < 3; i++)
            cube[int(FACE::DOWN)][i][2] = cube[int(FACE::BACK)][2 - i][0];
        for (int i = 0; i < 3; i++)
            cube[int(FACE::BACK)][2 - i][0] = cube[int(FACE::UP)][i][2];
        for (int i = 0; i < 3; i++)
            cube[int(FACE::UP)][i][2] = temp[i];

        return *this;
    }

    RubiksCube &rPrime() override
    {
        r();
        r();
        r();
        return *this;
    }

    RubiksCube &r2() override
    {
        r();
        r();
        return *this;
    }

    RubiksCube &f() override
    {
        rotateFace(FACE::FRONT);

        char temp[3];
        for (int i = 0; i < 3; i++)
            temp[i] = cube[int(FACE::UP)][2][i];

        for (int i = 0; i < 3; i++)
            cube[int(FACE::UP)][2][i] = cube[int(FACE::LEFT)][2 - i][2];
        for (int i = 0; i < 3; i++)
            cube[int(FACE::LEFT)][2 - i][2] = cube[int(FACE::DOWN)][0][2 - i];
        for (int i = 0; i < 3; i++)
            cube[int(FACE::DOWN)][0][2 - i] = cube[int(FACE::RIGHT)][i][0];
        for (int i = 0; i < 3; i++)
            cube[int(FACE::RIGHT)][i][0] = temp[i];

        return *this;
    }

    RubiksCube &fPrime() override
    {
        f();
        f();
        f();
        return *this;
    }

    RubiksCube &f2() override
    {
        f();
        f();
        return *this;
    }

    RubiksCube &b() override
    {
        rotateFace(FACE::BACK);

        char temp[3];
        for (int i = 0; i < 3; i++)
            temp[i] = cube[int(FACE::UP)][0][i];

        for (int i = 0; i < 3; i++)
            cube[int(FACE::UP)][0][i] = cube[int(FACE::RIGHT)][i][0];
        for (int i = 0; i < 3; i++)
            cube[int(FACE::RIGHT)][i][0] = cube[int(FACE::DOWN)][2][2 - i];
        for (int i = 0; i < 3; i++)
            cube[int(FACE::DOWN)][2][2 - i] = cube[int(FACE::LEFT)][2 - i][0];
        for (int i = 0; i < 3; i++)
            cube[int(FACE::LEFT)][2 - i][0] = temp[i];

        return *this;
    }

    RubiksCube &bPrime() override
    {
        b();
        b();
        b();
        return *this;
    }

    RubiksCube &b2() override
    {
        b();
        b();
        return *this;
    }

    RubiksCube3dArray &operator=(RubiksCube3dArray &rt)
    {
        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    cube[i][j][k] = rt.cube[i][j][k];
                }
            }
        }

        return *this;
    }

    bool operator==(RubiksCube3dArray &rt)
    {
        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    if (cube[i][j][k] != rt.cube[i][j][k])
                        return false;
                }
            }
        }
        return true;
    }
};