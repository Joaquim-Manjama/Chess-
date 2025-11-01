#include "piece.h"
#include <iostream>

// WILL CONTAIN SPECIFIC PIECE CLASSES INHERITING FROM THE PIECE CLASS

// Pawn Class
class Pawn : public Piece {
public:
	Pawn(std::string colour, Position position) : Piece(0, "PAWN", colour, position)
	{
		this->id = colour == "WHITE" ? 1 : -1;
		this->sizeOffset = -30;
	}

	std::vector<Position> GetPossibleTiles(int board[8][8])
	override {
		std::vector<Position> tiles;
		std::string white = "WHITE";

		if (hasMoved)
		{
			if (colour == white)
			{
				if (position.row > 0)
				{
					if (board[position.row - 1][position.column] == 0)
					{
						tiles.push_back(Position(position.row - 1, position.column));
					}
				}
			}
			else
			{
				if (position.row < 7)
				{
					if (board[position.row + 1][position.column] == 0)
					{
						tiles.push_back(Position(position.row + 1, position.column));
					}
				}
			}
		} 
		else
		{
			if (colour == white)
			{
				for (int i = 0; i < 2; i++)
				{
					if (board[position.row - (i + 1)][position.column] == 0)
					{
						tiles.push_back(Position(position.row - (i + 1), position.column));
					}

					if ((board[position.row - 2][position.column] != 0))
					{
						break;
					}
				}
			}
			else
			{
				for (int i = 0; i < 2; i++)
				{
					if (board[position.row + (i + 1)][position.column] == 0)
					{
						tiles.push_back(Position(position.row + (i + 1), position.column));
					}

					if ((board[position.row + 2][position.column] != 0))
					{
						break;
					}
				}
			}
		}

		if (colour == white)
		{
			if (position.row > 0)
			{
				if (position.column > 0)
				{
					if (OppositePiece(board, position.row - 1, position.column - 1))
					{
						tiles.push_back(Position(position.row - 1, position.column - 1));
					}
				}

				if (position.column < 7)
				{
					if (OppositePiece(board, position.row - 1, position.column + 1))
					{
						tiles.push_back(Position(position.row - 1, position.column + 1));
					}
				}
			}
		}
		else
		{
			if (position.row < 7)
			{
				if (position.column > 0)
				{
					if (OppositePiece(board, position.row + 1, position.column - 1))
					{
						tiles.push_back(Position(position.row + 1, position.column - 1));
					}
				}

				if (position.column < 7)
				{
					if (OppositePiece(board, position.row + 1, position.column + 1))
					{
						tiles.push_back(Position(position.row + 1, position.column + 1));
					}
				}
			}
		}

		return tiles;
	}
};

// Knight Class
class Knight : public Piece {
public:
	Knight(std::string colour, Position position) : Piece(0, "KNIGHT", colour, position)
	{
		this->id = colour == "WHITE" ? 2 : -2;
	}

	std::vector<Position> GetPossibleTiles(int board[8][8])
	override {
		std::vector<Position> tiles = {};
		int row;
		int column;

		// TOP SQUARES
		if (position.row > 1)
		{
			if (position.column > 0)
			{
				row = position.row - 2;
				column = position.column - 1;
				if (PossibleSquare(board, row, column))
				{
					tiles.push_back(Position(row, column));
				}
			}

			if (position.column < 7)
			{
				row = position.row - 2;
				column = position.column + 1;

				if (PossibleSquare(board, row, column))
				{
					tiles.push_back(Position(row, column));
				}
			}
		}

		// SIDE SQUARES

		// LEFT
		if (position.column > 1)
		{
			if (position.row > 0)
			{
				row = position.row - 1;
				column = position.column - 2;

				if (PossibleSquare(board, row, column))
				{
					tiles.push_back(Position(row, column));
				}
			}

			if (position.row < 7)
			{
				row = position.row + 1;
				column = position.column - 2;

				if (PossibleSquare(board, row, column))
				{
					tiles.push_back(Position(row, column));
				}
			}
		}

		// RIGHT
		if (position.column < 6)
		{
			if (position.row > 0)
			{
				row = position.row - 1;
				column = position.column + 2;

				if (PossibleSquare(board, row, column))
				{
					tiles.push_back(Position(row, column));
				}
			}

			if (position.row < 7)
			{
				row = position.row + 1;
				column = position.column + 2;

				if (PossibleSquare(board, row, column))
				{
					tiles.push_back(Position(row, column));
				}
			}
		}

		// BOTTOM
		if (position.row < 6)
		{
			if (position.column > 0)
			{
				row = position.row + 2;
				column = position.column - 1;

				if (PossibleSquare(board, row, column))
				{
					tiles.push_back(Position(row, column));
				}
			}

			if (position.column < 7)
			{
				row = position.row + 2;
				column = position.column + 1;

				if (PossibleSquare(board, row, column))
				{
					tiles.push_back(Position(row, column));
				}
			}
		}
		
		return tiles;
	}
};

// Bishop Class
class Bishop : public Piece {
public:
	Bishop(std::string colour, Position position) : Piece(0, "BISHOP", colour, position)
	{
		this->id = colour == "WHITE" ? 3 : -3;
	}

	std::vector<Position> GetPossibleTiles(int board[8][8])
	override{
		std::vector<Position> tiles = {};
		int nextRow;
		int nextColumn;

		// TOP LEFT DIAGONAL
		nextRow = position.row - 1;
		nextColumn = position.column - 1;

		while ((nextRow >= 0 && nextColumn >= 0) && PossibleSquare(board, nextRow, nextColumn))
		{
			tiles.push_back(Position(nextRow, nextColumn));
			nextRow--;
			nextColumn--;

			if (nextRow >= 0 && nextColumn >= 0)
			{
				if (OppositePiece(board, nextRow + 1, nextColumn + 1))
				{
					break;
				}
			}
		}

		// TOP RIGHT DIAGONAL
		nextRow = position.row - 1;
		nextColumn = position.column + 1;

		while ((nextRow >= 0 && nextColumn <= 7) && PossibleSquare(board, nextRow, nextColumn))
		{
			tiles.push_back(Position(nextRow, nextColumn));
			nextRow--;
			nextColumn++;

			if (nextRow >= 0 && nextColumn <= 7)
			{
				if (OppositePiece(board, nextRow + 1, nextColumn - 1))
				{
					break;
				}
			}
		}

		// BOTTOM LEFT DIAGONAL
		nextRow = position.row + 1;
		nextColumn = position.column - 1;

		while ((nextRow <= 7 && nextColumn >= 0) && PossibleSquare(board, nextRow, nextColumn))
		{
			tiles.push_back(Position(nextRow, nextColumn));
			nextRow++;
			nextColumn--;

			if (nextRow <= 7 && nextColumn >= 0)
			{
				if (OppositePiece(board, nextRow - 1, nextColumn + 1))
				{
					break;
				}
			}
		}

		// BOTTOM RIGHT DIAGONAL
		nextRow = position.row + 1;
		nextColumn = position.column + 1;

		while ((nextRow <= 7 && nextColumn <= 7) && PossibleSquare(board, nextRow, nextColumn))
		{
			tiles.push_back(Position(nextRow, nextColumn));
			nextRow++;
			nextColumn++;

			if (nextRow <= 7 && nextColumn <= 7)
			{
				if (OppositePiece(board, nextRow - 1, nextColumn - 1))
				{
					break;
				}
			}
		}

		return tiles;
	}
};

// Rook Class
class Rook : public Piece {
public:
	Rook(std::string colour, Position position) : Piece(0, "ROOK", colour, position)
	{
		this->id = colour == "WHITE" ? 4 : -4;
		this->sizeOffset = 0;
	}

	std::vector<Position> GetPossibleTiles(int board[8][8])
	override{
		std::vector<Position> tiles = {};
		int nextRow;
		int nextColumn;

		// TOP
		nextRow = position.row - 1;
		nextColumn = position.column;

		while (nextRow >= 0 && PossibleSquare(board, nextRow, nextColumn))
		{
			tiles.push_back(Position(nextRow, nextColumn));

			nextRow--;

			if (nextRow >= 0)
			{
				if (OppositePiece(board, nextRow + 1, nextColumn))
				{
					break;
				}
			}
		}

		// BOTTOM
		nextRow = position.row + 1;
		nextColumn = position.column;

		while (nextRow <= 7 && PossibleSquare(board, nextRow, nextColumn))
		{
			tiles.push_back(Position(nextRow, nextColumn));

			nextRow++;

			if (nextRow <= 7)
			{
				if (OppositePiece(board, nextRow - 1, nextColumn))
				{
					break;
				}
			}
		}

		// LEFT
		nextRow = position.row;
		nextColumn = position.column - 1;

		while (nextColumn >= 0 && PossibleSquare(board, nextRow, nextColumn))
		{
			tiles.push_back(Position(nextRow, nextColumn));

			nextColumn--;

			if (nextColumn >= 0)
			{
				if (OppositePiece(board, nextRow, nextColumn + 1))
				{
					break;
				}
			}
		}

		// RIGHT
		nextRow = position.row;
		nextColumn = position.column + 1;

		while (nextColumn <= 7 && PossibleSquare(board, nextRow, nextColumn))
		{
			tiles.push_back(Position(nextRow, nextColumn));

			nextColumn++;

			if (nextColumn <= 7)
			{
				if (OppositePiece(board, nextRow, nextColumn - 1))
				{
					break;
				}
			}
		}

		return tiles;
	}
};

// Queen Class
class Queen : public Piece {
public:
	Queen(std::string colour, Position position) : Piece(0, "QUEEN", colour, position)
	{
		this->id = colour == "WHITE" ? 5 : -5;
	}

	std::vector<Position> GetPossibleTiles(int board[8][8])
	override {
		std::vector<Position> tiles = {};

		Bishop bishop = Bishop(colour, position);
		Rook rook = Rook(colour, position);

		for (Position tile : bishop.GetPossibleTiles(board))
		{
			tiles.push_back(tile);
		}

		for (Position tile : rook.GetPossibleTiles(board))
		{
			tiles.push_back(tile);
		}

		return tiles;
	}
};

// King Class
class King : public Piece {
public:
	King(std::string colour, Position position) : Piece(0, "KING", colour, position)
	{
		this->id = colour == "WHITE" ? 6 : -6;
	}

	std::vector<Position> GetPossibleTiles(int board[8][8])
	override {
		std::vector<Position> tiles;

		// UP
		if (position.row > 0)
		{
			if (PossibleSquare(board, position.row - 1, position.column))
			{
				tiles.push_back(Position(position.row - 1, position.column));
			}
		}

		// UP RIGHT
		if (position.row > 0 && position.column < 7)
		{
			if (PossibleSquare(board, position.row - 1, position.column + 1))
			{
				tiles.push_back(Position(position.row - 1, position.column + 1));
			}
		}

		// RIGHT
		if (position.column < 7)
		{
			if (PossibleSquare(board, position.row, position.column + 1))
			{
				tiles.push_back(Position(position.row, position.column + 1));
			}
		}

		// BOTTOM RIGHT
		if (position.row < 7 && position.column < 7)
		{
			if (PossibleSquare(board, position.row + 1, position.column + 1))
			{
				tiles.push_back(Position(position.row + 1, position.column + 1));
			}
		}

		// BOTTOM
		if (position.row < 7)
		{
			if (PossibleSquare(board, position.row + 1, position.column))
			{
				tiles.push_back(Position(position.row + 1, position.column));
			}
		}

		// BOTTOM LEFT
		if (position.row < 7 && position.column > 0)
		{
			if (PossibleSquare(board, position.row + 1, position.column - 1))
			{
				tiles.push_back(Position(position.row + 1, position.column - 1));
			}
		}

		// LEFT
		if (position.column > 0)
		{
			if (PossibleSquare(board, position.row, position.column - 1))
			{
				tiles.push_back(Position(position.row, position.column - 1));
			}
		}

		// UP LEFT
		if (position.row > 0 && position.column > 0)
		{
			if (PossibleSquare(board, position.row - 1, position.column - 1))
			{
				tiles.push_back(Position(position.row - 1, position.column - 1));
			}
		}

		// CASTLES
		if (!hasMoved)
		{
			// KING SIDE
			if (CanCastleKingSide(board))
			{
				tiles.push_back(Position(position.row, position.column + 2));
			}

			// QUEEN SIDE
			if (CanCastleQueenSide(board))
			{
				tiles.push_back(Position(position.row, position.column - 2));
			}
		}


		return tiles;
	}

	// Check if King Can Castle King Side
	bool CanCastleKingSide(int board[8][8])
	{
		std::string white = "WHITE";

		if (true)//colour == white)
		{
			if (board[position.row][position.column + 1] == board[position.row][position.column + 2] && board[position.row][position.column + 1] == 0)
			{
				if (abs(board[position.row][position.column + 3]) == 4 && !OppositePiece(board, position.row, position.column + 3))
				{
					return true;
				}
			}
		}
		/*else
		{
			if (board[position.row][position.column - 1] == board[position.row][position.column - 2] && board[position.row][position.column - 1] == 0)
			{
				if (abs(board[position.row][position.column - 3]) == 4 && !OppositePiece(board, position.row, position.column - 3))
				{
					return true;
				}
			}
		}*/
		return false;
	}

	// Check if King Can Castle Queen Side
	bool CanCastleQueenSide(int board[8][8])
	{
		std::string white = "WHITE";

		if (true)//colour == white)
		{
			if (board[position.row][position.column - 1] == board[position.row][position.column - 2] && board[position.row][position.column - 2] == board[position.row][position.column - 3] && board[position.row][position.column - 3] == 0)
			{
				if (abs(board[position.row][position.column - 4]) == 4 && !OppositePiece(board, position.row, position.column - 4))
				{
					return true;
				}
			}
		}
		/*else
		{
			if (board[position.row][position.column + 1] == board[position.row][position.column + 2] && board[position.row][position.column + 2] == board[position.row][position.column + 3] && board[position.row][position.column + 3] == 0)
			{
				if (abs(board[position.row][position.column + 4]) == 4 && !OppositePiece(board, position.row, position.column + 4))
				{
					return true;
				}
			}
		}*/
		return false;
	}
};

