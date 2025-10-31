#pragma once
#include <raylib.h>
#include <string>
#include "position.h"
#include "imageUtil.h"

class Piece {
public:
	Piece();
	Piece(int id, std::string type, std::string colour, Position position);
	Texture2D texture;
	virtual std::vector<Position> GetPossibleTiles(int board[8][8]);
	int id;
	int sizeOffset;
	std::string type;
	std::string colour;
	bool hasMoved;
	Position position;
	void Draw(int cellSize);
	void Move(Position position);
	bool PossibleSquare(int board[8][8], int row, int column);
	bool OppositePiece(int board[8][8], int row, int column);

private:
	ImageUtil imageUtil;
};