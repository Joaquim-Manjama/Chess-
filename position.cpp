#include "position.h"

// Position Constructor
Position::Position(int row, int column)
{
	this->row = row;
	this->column = column;
}

Position::Position()
{
	this->row = -1;
	this->column = -1;
}

std::vector<int> Position::Display()
{
	std::vector<int> values = { row, column };
	return values;
}
