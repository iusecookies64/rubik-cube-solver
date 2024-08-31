
#ifndef RUBIKS_CUBE_SOLVER_RUBIKSCUBE_H
#define RUBIKS_CUBE_SOLVER_RUBIKSCUBE_H

#include <bits/stdc++.h>
using namespace std;

class RubiksCube
{
public:
  // faces of cube
  enum class FACE
  {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    FRONT,
    BACK
  };
  // color of faces (in same order as faces)
  enum class COLOR
  {
    WHITE,
    YELLOW,
    GREEN,
    BLUE,
    RED,
    ORANGE,
  };

  enum class MOVE
  {
    L,
    LPRIME,
    L2,
    R,
    RPRIME,
    R2,
    U,
    UPRIME,
    U2,
    D,
    DPRIME,
    D2,
    F,
    FPRIME,
    F2,
    B,
    BPRIME,
    B2
  };

  // to get color of specified face, row, col
  virtual COLOR getColor(FACE face, unsigned row, unsigned col) const = 0;

  static COLOR getColorFromChar(char colorChar);

  // to get color character corresponding to color enum
  static char getColorLetter(COLOR color);

  static string getMove(MOVE move);

  virtual bool isSolved() const = 0;

  void print() const;

  vector<MOVE> randomShuffle(unsigned int times);

  RubiksCube &move(MOVE move);

  RubiksCube &invert(MOVE move);

  virtual RubiksCube &f() = 0;

  RubiksCube &fPrime();

  RubiksCube &f2();

  virtual RubiksCube &b() = 0;

  RubiksCube &bPrime();

  RubiksCube &b2();

  virtual RubiksCube &l() = 0;

  RubiksCube &lPrime();

  RubiksCube &l2();

  virtual RubiksCube &r() = 0;

  RubiksCube &rPrime();

  RubiksCube &r2();

  virtual RubiksCube &u() = 0;

  RubiksCube &uPrime();

  RubiksCube &u2();

  virtual RubiksCube &d() = 0;

  RubiksCube &dPrime();

  RubiksCube &d2();

  string getCornerColorString(uint8_t ind) const;

  uint8_t getCornerIndex(uint8_t ind) const;

  uint8_t getCornerOrientation(uint8_t ind) const;
};

#endif // RUBIKS_CUBE_SOLVER_RUBIKSCUBE_H