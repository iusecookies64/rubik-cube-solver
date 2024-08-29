
#include "RubiksCube.h"

char RubiksCube::getColorLetter(COLOR color)
{
	switch (color)
	{
	case COLOR::BLUE:
		return 'B';
	case COLOR::RED:
		return 'R';
	case COLOR::GREEN:
		return 'G';
	case COLOR::WHITE:
		return 'W';
	case COLOR::YELLOW:
		return 'Y';
	case COLOR::ORANGE:
		return 'O';
	default:
		return 'G';
	}
}

RubiksCube::COLOR RubiksCube::getColorFromChar(char colorChar)
{
	switch (colorChar)
	{
	case 'B':
		return COLOR::BLUE;
	case 'G':
		return COLOR::GREEN;
	case 'Y':
		return COLOR::YELLOW;
	case 'R':
		return COLOR::RED;
	case 'O':
		return COLOR::ORANGE;
	case 'W':
		return COLOR::WHITE;
	default:
		return COLOR::BLUE;
	}
}

string RubiksCube::getMove(MOVE move)
{
	switch (move)
	{
	case MOVE::L:
		return "L";
	case MOVE::LPRIME:
		return "LPRIME";
	case MOVE::L2:
		return "L2";
	case MOVE::R:
		return "R";
	case MOVE::RPRIME:
		return "RPRIME";
	case MOVE::R2:
		return "R2";
	case MOVE::U:
		return "U";
	case MOVE::UPRIME:
		return "UPRIME";
	case MOVE::U2:
		return "U2";
	case MOVE::D:
		return "D";
	case MOVE::DPRIME:
		return "DPRIME";
	case MOVE::D2:
		return "D2";
	case MOVE::F:
		return "F";
	case MOVE::FPRIME:
		return "FPRIME";
	case MOVE::F2:
		return "F2";
	case MOVE::B:
		return "B";
	case MOVE::BPRIME:
		return "BPRIME";
	case MOVE::B2:
		return "B2";
	default:
		return "Invalid Move";
	}
}

RubiksCube &RubiksCube::move(MOVE move)
{
	switch (move)
	{
	case MOVE::L:
		return l();
	case MOVE::LPRIME:
		return lPrime();
	case MOVE::L2:
		return l2();
	case MOVE::R:
		return r();
	case MOVE::RPRIME:
		return rPrime();
	case MOVE::R2:
		return r2();
	case MOVE::U:
		return u();
	case MOVE::UPRIME:
		return uPrime();
	case MOVE::U2:
		return u2();
	case MOVE::D:
		return d();
	case MOVE::DPRIME:
		return dPrime();
	case MOVE::D2:
		return d2();
	case MOVE::F:
		return f();
	case MOVE::FPRIME:
		return fPrime();
	case MOVE::F2:
		return f2();
	case MOVE::B:
		return b();
	case MOVE::BPRIME:
		return bPrime();
	case MOVE::B2:
		return b2();
	default:
		return *this;
	}
}

RubiksCube &RubiksCube::invert(MOVE move)
{
	switch (move)
	{
	case MOVE::L:
		return lPrime();
	case MOVE::LPRIME:
		return l();
	case MOVE::L2:
		return l2();
	case MOVE::R:
		return rPrime();
	case MOVE::RPRIME:
		return r();
	case MOVE::R2:
		return r2();
	case MOVE::U:
		return uPrime();
	case MOVE::UPRIME:
		return u();
	case MOVE::U2:
		return u2();
	case MOVE::D:
		return dPrime();
	case MOVE::DPRIME:
		return d();
	case MOVE::D2:
		return d2();
	case MOVE::F:
		return fPrime();
	case MOVE::FPRIME:
		return f();
	case MOVE::F2:
		return f2();
	case MOVE::B:
		return bPrime();
	case MOVE::BPRIME:
		return b();
	case MOVE::B2:
		return b2();
	default:
		return *this;
	}
}

void RubiksCube::print() const
{
	cout << "Rubik's Cube\n\n";

	for (int row = 0; row <= 2; row++)
	{
		// initial empty spaces
		for (int col = 0; col < 7; col++)
		{
			cout << ' ';
		}
		// printing face up of the cube
		for (int col = 0; col <= 2; col++)
		{
			cout << getColorLetter(getColor(FACE::UP, row, col)) << ' ';
		}
		cout << '\n';
	}
	cout << '\n';

	for (int row = 0; row <= 2; row++)
	{
		// printing the face left
		for (int col = 0; col <= 2; col++)
		{
			cout << getColorLetter(getColor(FACE::LEFT, row, col)) << ' ';
		}
		cout << ' ';
		// printing the front face
		for (int col = 0; col <= 2; col++)
		{
			cout << getColorLetter(getColor(FACE::FRONT, row, col)) << ' ';
		}
		cout << ' ';
		// printing the right face
		for (int col = 0; col <= 2; col++)
		{
			cout << getColorLetter(getColor(FACE::RIGHT, row, col)) << ' ';
		}
		cout << ' ';
		// printing the back side
		for (int col = 0; col <= 2; col++)
		{
			cout << getColorLetter(getColor(FACE::BACK, row, col)) << ' ';
		}
		cout << '\n';
	}
	cout << '\n';

	// printing the bottom face
	for (int row = 0; row <= 2; row++)
	{
		// printing the initial white spaces
		for (int i = 0; i < 7; i++)
		{
			cout << ' ';
		}
		// printing the down face
		for (int col = 0; col <= 2; col++)
		{
			cout << getColorLetter(getColor(FACE::DOWN, row, col)) << ' ';
		}
		cout << '\n';
	}
	cout << '\n';
}

vector<RubiksCube::MOVE> RubiksCube::randomShuffle(unsigned int times)
{
	vector<MOVE> moves_performed;
	// random seed
	srand(time(0));
	for (unsigned int i = 0; i < times; i++)
	{
		// getting a random move
		unsigned int selectedMove = (rand() % 18);
		// storing move in moves vector
		moves_performed.push_back(static_cast<MOVE>(selectedMove));
		// performing the move
		move(static_cast<MOVE>(selectedMove));
	}
	return moves_performed;
}