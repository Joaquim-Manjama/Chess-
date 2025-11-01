#include <iostream>
#include <raylib.h>
#include "board.h"
#include "pieces.cpp"


// Board Constructor
Board::Board()
{
	// Board Measurements
	rows = 8;
	columns = 8;
	cellSize = 100;

	// Piece Initial Positions per type
	pawnPositions = {	// White Pawns
						Position(6, 0), Position(6, 1), Position(6, 2), Position(6, 3), 
						Position(6, 4), Position(6, 5), Position(6, 6), Position(6, 7),

						//Black Pawns
						Position(1, 0), Position(1, 1), Position(1, 2), Position(1, 3), 
						Position(1, 4), Position(1, 5), Position(1, 6), Position(1, 7) };

	knightPositions = { // White Knights
						Position(7, 1), Position(7, 6), 

						//Black Knights
						Position(0, 1), Position(0, 6)};

	bishopPositions = {	// White Bishops
						Position(7, 2), Position(7, 5), 
						
						// Black Bishops
						Position(0, 2), Position(0, 5)
					};

	rookPositions = {	// White Rooks
						Position(7, 0), Position(7, 7),

						// Black Rooks
						Position(0, 0), Position(0, 7)
					};

	queenPositions = {	//White Queen
						Position(7, 3), 
						
						//Black Queen
						Position(0, 3)
					};

	kingPositions = {	//White King
						Position(7, 4),

						//Black King
						Position(0, 4)
	};;
	
	// Inititalize Board
	Initialize();
}

// Method that will initialize the board
void Board::Initialize()
{
	InitializeBoard();
	InitPieces();
	LockPieces();
}

void Board::InitializeBoard()
{
	for (int row = 0; row < rows; row++)
	{
		for (int column = 0; column < columns; column++)
		{
			board[row][column] = 0;
		}
	}
}

// Method that will initialize each piece type
void Board::InitPiece(const std::vector<Position> positions, int id)
{
	int half = positions.size() / 2;

	for (int i = 0; i < positions.size(); ++i)
	{
		std::string color = (i < half) ? "WHITE" : "BLACK";
		Position pos = positions[i];

		// Pawns
		if (id == 1)
		{
			pieces.push_back(std::make_unique<Pawn>(color, pos));
		}

		// Bishops
		if (id == 2)
		{
			pieces.push_back(std::make_unique<Knight>(color, pos));
		}

		// Knight
		if (id == 3)
		{
			pieces.push_back(std::make_unique<Bishop>(color, pos));
		}

		// Rook
		if (id == 4)
		{
			pieces.push_back(std::make_unique<Rook>(color, pos));
		}

		// Queen
		if (id == 5)
		{
			pieces.push_back(std::make_unique<Queen>(color, pos));
		}

		// King
		if (id == 6)
		{
			pieces.push_back(std::make_unique<King>(color, pos));
		}
	}
}

// Initialize all Pieces
void Board::InitPieces()
{
	InitPiece(pawnPositions, 1);
	InitPiece(knightPositions, 2);
	InitPiece(bishopPositions, 3);
	InitPiece(rookPositions, 4);
	InitPiece(queenPositions, 5);
	InitPiece(kingPositions, 6);
}

// Draw the Board, Tiles and Pieces
void Board::Draw(int row, int column) 
{
	// Draw Board
	Color white = { 244, 194, 194, 255 };
	Color black = { 0, 0, 0, 255 };

	// Offset 
	int offset = 2;


	for (int row = 0; row < rows; row++) 
	{
		for (int column = 0; column < columns; column++) 
		{
			if (row % 2 == 0)
			{	
				if (column % 2 == 0)
				{
					DrawRectangle(row * cellSize + offset, column * cellSize + offset, cellSize - (offset * 2), cellSize - (offset * 2), black);
				}
				else
				{
					DrawRectangle(row * cellSize + offset, column * cellSize + offset, cellSize - (offset * 2), cellSize - (offset * 2), white);
				}
			}
			else
			{
				if (column % 2 != 0)
				{
					DrawRectangle(row * cellSize + offset, column * cellSize + offset, cellSize - (offset * 2), cellSize - (offset * 2), black);
				}
				else
				{
					DrawRectangle(row * cellSize + offset, column * cellSize + offset, cellSize - (offset * 2), cellSize - (offset * 2), white);
				}
			}
		}
	}

	// Draw Tiles

	// Selected Tile
	if (selectedTile.row >= 0)
	{
		DrawRectangle(selectedTile.column * cellSize + offset, selectedTile.row * cellSize + offset, cellSize - (offset * 2), cellSize - (offset * 2), BLUE);
	}

	// Possible Tile
	for (Position tile : possibleTiles)
	{
		DrawRectangle(tile.column * cellSize + offset, tile.row * cellSize + offset, cellSize - (offset * 2), cellSize - (offset * 2), GREEN);
	}

	// Danger Tile
	for (Position tile : dangerTiles)
	{
		DrawRectangle(tile.column * cellSize + offset, tile.row * cellSize + offset, cellSize - (offset * 2), cellSize - (offset * 2), RED);
	}

	// Cursor Tile
	DrawRectangle(column * cellSize + offset, row * cellSize + offset, cellSize - (offset * 2), cellSize - (offset * 2), Color {255, 255, 255, 133});

	// Draw Pieces
	for (auto& piece : pieces)
	{
		piece->Draw(cellSize);
	}
}

// Print out the Board
void Board::Print()
{
	for (int row = 0; row < rows; row++)
	{
		for (int column = 0; column < columns; column++)
		{
			std::cout << board[row][column];
		}

		std::cout << std::endl;
	}
}

// Update the board grid
void Board::LockPieces()
{
	for (auto& piece : pieces)
	{
		board[piece->position.row][piece->position.column] = piece->id;
	}
}

// Selects a Tile
bool Board::SelectTile(Position position, bool turn)
{
	selectedTile = Position();
	possibleTiles = {};
	dangerTiles = {};
	std::string king = "KING";
	
	if (PiecePresent(position))
	{
		currentPiece = GetPiece(position);

		if (turn && currentPiece.colour == "WHITE" || !turn && currentPiece.colour == "BLACK")
		{
			selectedTile = position;
			possibleTiles = GetPiece(position).GetPossibleTiles(board);

			if (currentPiece.type == king)
			{
				RemoveAttackedSquares(turn);
			}

			dangerTiles = GetDangerTiles(turn);

			return true;
		}
	}

	return false;
}

// Check if Piece in Position
bool Board::PiecePresent(Position position) {
	for (auto& piece : pieces)
	{
		if (piece->position.Display() == position.Display())
		{
			return true;
		}
	}
	return false;
}

// Get Piece at Location
Piece& Board::GetPiece(Position position) {
	for (auto& piece : pieces)
	{
		if (piece->position.Display() == position.Display())
		{
			return *piece;
		}
	}
	return *pieces[0];
}

// Check if tile can be moved to
bool Board::PossibleTile(int row, int column)
{
	for (Position position : possibleTiles)
	{
		if (position.row == row && position.column == column)
		{
			return true;
		}
	}

	return false;
}

// Erase Possible tiles stored
void Board::RemovePossibleTiles()
{
	possibleTiles = {};
	dangerTiles = {};
	selectedTile = Position();
}

// Move a piece in the board
bool Board::MovePiece(int row, int column)
{
	Position newPosition(row, column);

	pieces.erase(
		std::remove_if(
			pieces.begin(),
			pieces.end(),
			[&](const std::unique_ptr<Piece>& piece)
			{
				return piece->position.Display() == newPosition.Display();
			}),
		pieces.end()
	);

	for (auto& piece : pieces)
	{
		if (piece->position.Display() == currentPiece.position.Display())
		{
			// Castle King Side
			if (piece->type == "KING" && newPosition.column == piece->position.column + 2)
			{
				Castle(piece->position.row, piece->position.column + 3, -2);
			}

			// Castle Queen Side
			if (piece->type == "KING" && newPosition.column == piece->position.column - 2)
			{
				Castle(piece->position.row, piece->position.column - 4, 3);
			}
			piece->Move(newPosition);
			break;
		}
	}

	InitializeBoard();
	LockPieces();

	return true;
}

// Castle the king by moving rook
void Board::Castle(int row, int column, int move)
{
	Position newPosition = Position(row, column);

	for (auto& piece : pieces)
	{
		if (piece->position.Display() == newPosition.Display())
		{
			newPosition.column += move;

			if (!piece->hasMoved)
			{
				piece->Move(newPosition);
			}
		}
	}
}

std::vector<Position> Board::GetDangerTiles(bool turn)
{
	std::vector<Position> tiles = {};
	std::string white = "WHITE";

	for (auto& tile : possibleTiles)
	{
		if (PiecePresent(tile))
		{
			if (GetPiece(tile).colour == white && !turn)
			{
				tiles.push_back(tile);
			}

			if (GetPiece(tile).colour != white && turn)
			{
				tiles.push_back(tile);
			}
		}
	}
	return tiles;
}

bool Board::SquareUnderAttack(Position position, bool turn)
{
	std::vector<Position> tiles = {};
	std::vector<Position> dummyTiles = {};
	std::string colour = "WHITE";

	for (auto& piece : pieces)
	{
		if (piece->colour == colour && !turn)
		{
			dummyTiles = piece->GetPossibleTiles(board);
			tiles.insert(tiles.end(), dummyTiles.begin(), dummyTiles.end());
		}

		if (piece->colour != colour && turn)
		{
			dummyTiles = piece->GetPossibleTiles(board);
			tiles.insert(tiles.end(), dummyTiles.begin(), dummyTiles.end());
		}
	}

	for (auto& tile: tiles)
	{
		if (tile.Display() == position.Display())
		{
			return true;
		}
	}

	return false;
}

void Board::RemoveAttackedSquares(bool turn)
{
	for (auto& position : possibleTiles)
	{
		if (SquareUnderAttack(position, turn))
		{
			possibleTiles.erase(
				std::remove_if(
					possibleTiles.begin(),
					possibleTiles.end(),
					[&](const Position& pos) {
						return pos.row == position.row && pos.column == position.column;
					}
				),
				possibleTiles.end()
			);
		}
	}
}

void Board::RemoveCastlingRights()
{

}

// Flip the Board 
// Currently not being used
void Board::FlipBoard()
{
	// FLIP PIECES
	for (auto& piece : pieces)
	{
		piece->position.row = 7 - piece->position.row;
		piece->position.column = 7 - piece->position.column;
	}

	InitializeBoard();
	LockPieces();
}