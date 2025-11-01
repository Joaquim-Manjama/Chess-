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
	void Print();
	void RemovePossibleTiles();

	bool MovePiece(int row, int column);
	bool PossibleTile(int row, int column);
	bool SelectTile(Position position, bool turn);

private:	
	void Castle(int row, int column, int move);
	void FlipBoard();
	void Initialize();
	void InitializeBoard();
	void InitPiece(std::vector<Position> positions, int id);
	void InitPieces();
	void LockPieces();
	void RemoveAttackedSquares(bool turn);
	void RemoveCastlingRights();
	
	bool SquareUnderAttack(Position position, bool turn);
	bool PiecePresent(Position position);

	Piece& GetPiece(Position position);

	std::vector<Position> GetDangerTiles(bool turn);

	int board[8][8];
	int cellSize;
	int columns;
	int rows;
	
	Piece currentPiece;
	
	Position selectedTile;
	
	std::vector<Position> bishopPositions;
	std::vector<Position> dangerTiles;
	std::vector<Position> kingPositions;
	std::vector<Position> knightPositions;
	std::vector<Position> pawnPositions;
	std::vector<Position> possibleTiles;
	std::vector<Position> queenPositions;
	std::vector<Position> rookPositions;

	std::vector<std::unique_ptr<Piece>> pieces;
};