
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
	auto now = std::chrono::high_resolution_clock::now();
	unsigned int seed = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()).count();

	// random seed
	srand(seed);
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

RubiksCube &RubiksCube::uPrime()
{
	u();
	u();
	u();
	return *this;
}

RubiksCube &RubiksCube::u2()
{
	u();
	u();
	return *this;
}

RubiksCube &RubiksCube::dPrime()
{
	d();
	d();
	d();
	return *this;
}

RubiksCube &RubiksCube::d2()
{
	d();
	d();
	return *this;
}

RubiksCube &RubiksCube::lPrime()
{
	l();
	l();
	l();
	return *this;
}

RubiksCube &RubiksCube::l2()
{
	l();
	l();
	return *this;
}

RubiksCube &RubiksCube::rPrime()
{
	r();
	r();
	r();
	return *this;
}

RubiksCube &RubiksCube::r2()
{
	r();
	r();
	return *this;
}

RubiksCube &RubiksCube::fPrime()
{
	f();
	f();
	f();
	return *this;
}

RubiksCube &RubiksCube::f2()
{
	f();
	f();
	return *this;
}

RubiksCube &RubiksCube::bPrime()
{
	b();
	b();
	b();
	return *this;
}

RubiksCube &RubiksCube::b2()
{
	b();
	b();
	return *this;
}

// the corners are indexed using 3 bits
// up/down is decided by 2nd bit (i.e bit 2^2), u -> bit not set, d -> bit set
// front/back is decided by 1st bit, f -> not set, b -> set
// right/left is decided by 0th bit, r -> not set, l -> set
string RubiksCube::getCornerColorString(uint32_t index) const
{
	string res = "";
	switch (index)
	{
	// UFR
	case 0:
		res += getColorLetter(getColor(FACE::UP, 2, 2));
		res += getColorLetter(getColor(FACE::FRONT, 0, 2));
		res += getColorLetter(getColor(FACE::RIGHT, 0, 0));
		break;
	// UFL
	case 1:
		res += getColorLetter(getColor(FACE::UP, 2, 0));
		res += getColorLetter(getColor(FACE::FRONT, 0, 0));
		res += getColorLetter(getColor(FACE::LEFT, 0, 2));
		break;
	// UBR
	case 2:
		res += getColorLetter(getColor(FACE::UP, 0, 2));
		res += getColorLetter(getColor(FACE::BACK, 0, 0));
		res += getColorLetter(getColor(FACE::RIGHT, 0, 2));
		break;
	// UBL
	case 3:
		res += getColorLetter(getColor(FACE::UP, 0, 0));
		res += getColorLetter(getColor(FACE::BACK, 0, 2));
		res += getColorLetter(getColor(FACE::LEFT, 0, 0));
		break;
	// DFR
	case 4:
		res += getColorLetter(getColor(FACE::DOWN, 0, 2));
		res += getColorLetter(getColor(FACE::FRONT, 2, 2));
		res += getColorLetter(getColor(FACE::RIGHT, 2, 0));
		break;
	// DFL
	case 5:
		res += getColorLetter(getColor(FACE::DOWN, 0, 0));
		res += getColorLetter(getColor(FACE::FRONT, 2, 0));
		res += getColorLetter(getColor(FACE::LEFT, 2, 2));
		break;
	// DBR
	case 6:
		res += getColorLetter(getColor(FACE::DOWN, 2, 2));
		res += getColorLetter(getColor(FACE::BACK, 2, 0));
		res += getColorLetter(getColor(FACE::RIGHT, 2, 2));
		break;
	// DBL
	case 7:
		res += getColorLetter(getColor(FACE::DOWN, 2, 0));
		res += getColorLetter(getColor(FACE::BACK, 2, 2));
		res += getColorLetter(getColor(FACE::LEFT, 2, 0));
		break;
	default:
		break;
	}

	return res;
}

// given a corner index return the actual index of the corner cubie (in solved cube)
uint32_t RubiksCube::getCornerIndex(uint32_t index) const
{
	string cornerString = getCornerColorString(index);

	uint32_t res = 0;
	// checking for 0th bit
	char c = getColorLetter(COLOR(int(FACE::LEFT))); // color of left face in solved cube
	if (cornerString.find(c) != string::npos)
	{
		res |= 1;
	}

	// checking for 1st bit
	c = getColorLetter(COLOR(int(FACE::BACK))); // color of back face in solved cube
	if (cornerString.find(c) != string::npos)
	{
		res |= (1 << 1);
	}

	// checkinf for 2nd bit
	c = getColorLetter(COLOR(int(FACE::DOWN))); // color of down face in solved cube
	if (cornerString.find(c) != string::npos)
	{
		res |= (1 << 2);
	}

	return res;
}

// orientation is decided based on where up/down is present in the corner string
// 0 => up/down on 0th index (default orientation)
// 1 => up/down on 1st index
// 2 => up/down on 2nd index
uint32_t RubiksCube::getCornerOrientation(uint32_t index) const
{
	string cornerString = getCornerColorString(index);

	// finding which of up/down color is present in the string
	char c = getColorLetter(COLOR(int(FACE::UP)));
	if (cornerString.find(c) == string::npos)
	{
		c = getColorLetter(COLOR(int(FACE::DOWN)));
	}

	if (cornerString[0] == c)
		return 0;
	else if (cornerString[1] == c)
		return 1;
	else
		return 2;
}