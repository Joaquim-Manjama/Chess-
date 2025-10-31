#include <iostream>
#include "piece.h"
#include "pieces.cpp"


// Default Constructor
Piece::Piece()
{
}


// Piece Constructor
Piece::Piece(int id, std::string type, std::string colour, Position position)
	: id(id), type(type), colour(colour), hasMoved(false), position(position)
{
}


// Draw the piece
void Piece::Draw(int cellSize)
{
	if (type == "PAWN")
	{
		std::string dir = "Graphics/" + colour + "_" + type + ".png";
		imageUtil.DrawImage(dir, position, cellSize, sizeOffset);
	}
	else if (type == "ROOK")
	{
		std::string dir = "Graphics/" + colour + "_" + type + ".png";
		imageUtil.DrawImage(dir, position, cellSize, sizeOffset);
	}
	else 
	{
		std::string text = colour + '\n' + type;
		DrawText(text.c_str(), position.column * cellSize + cellSize / 10, position.row * cellSize + cellSize / 10, 20, BLUE);
	}
}

// Move the Piece
void Piece::Move(Position position)
{
	this->hasMoved = true;
	this->position = position;
}

bool Piece::PossibleSquare(int board[8][8], int row, int column)
{
	return board[row][column] * id <= 0;
}

bool Piece::OppositePiece(int board[8][8], int row, int column)
{
	return board[row][column] * id < 0;
}

// Declaration of Method
std::vector<Position> Piece::GetPossibleTiles(int board[8][8])
{
	std::vector<Position> tiles = {};

	return tiles;
}