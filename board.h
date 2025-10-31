#pragma once
#include <vector>
#include <memory>
#include "piece.h"
#include "position.h"

class Board 
{
public:
	Board();
	void Draw(int row, int column);
	void Update();
	void Print();
	void LockPieces();
	bool SelectTile(Position position, bool turn);
	bool PiecePresent(Position position);
	Piece& GetPiece(Position position);
	bool PossibleTile(int row, int column);
	void RemovePossibleTiles();
	void MovePiece(int row, int column);
private:	
	void Initialize();
	void InitPiece(std::vector<Position> positions, int id);
	void InitPieces();
	void InitializeBoard();
	int rows;
	int columns;
	int cellSize;
	int board[8][8];
	Position selectedTile;
	Piece currentPiece;
	std::vector<std::unique_ptr<Piece>> pieces;
	std::vector<Position> pawnPositions;
	std::vector<Position> knightPositions;
	std::vector<Position> bishopPositions;
	std::vector<Position> rookPositions;
	std::vector<Position> queenPositions;
	std::vector<Position> kingPositions;
	std::vector<Position> possibleTiles;
};