#pragma once
#include <vector>
class Position {
public:
	Position();
	Position(int row, int column);
	std::vector<int> Display();
	int row;
	int column;
};
