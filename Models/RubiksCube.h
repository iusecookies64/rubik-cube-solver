
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
    BLUE,
    GREEN,
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

  virtual RubiksCube &fPrime() = 0;

  virtual RubiksCube &f2() = 0;

  virtual RubiksCube &b() = 0;

  virtual RubiksCube &bPrime() = 0;

  virtual RubiksCube &b2() = 0;

  virtual RubiksCube &l() = 0;

  virtual RubiksCube &lPrime() = 0;

  virtual RubiksCube &l2() = 0;

  virtual RubiksCube &r() = 0;

  virtual RubiksCube &rPrime() = 0;

  virtual RubiksCube &r2() = 0;

  virtual RubiksCube &u() = 0;

  virtual RubiksCube &uPrime() = 0;

  virtual RubiksCube &u2() = 0;

  virtual RubiksCube &d() = 0;

  virtual RubiksCube &dPrime() = 0;

  virtual RubiksCube &d2() = 0;

  string getCornerColorString(uint8_t ind) const;

  uint8_t getCornerIndex(uint8_t ind) const;

  uint8_t getCornerOrientation(uint8_t ind) const;
};

#endif // RUBIKS_CUBE_SOLVER_RUBIKSCUBE_H