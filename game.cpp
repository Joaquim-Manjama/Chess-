#include "game.h"
#include "position.h"
#include <iostream>

// Game Constructor
Game::Game()
{
	Board board = Board();
	this->gameStatuses = {"choose piece", "play"}; // <-|
	this->gameStatus = 0; // Index of gameStatuses     -| 
	this->turn = true; // true -> WHITE | false -> BLACK
}

// Draw Game elements
void Game::Draw(int row, int column)
{
	board.Draw(row, column);
}

// Print the Board grid
void Game::PrintBoard()
{
	board.Print();
}

// Select a Tile
void Game::SelectTile(int row, int column)
{
	if (gameStatus == 0)
	{
		if (board.SelectTile(Position(row, column), turn))
		{
			gameStatus = 1;
		}
	}
	else
	{
		if (board.PossibleTile(row, column))
		{
			if (board.MovePiece(row, column));
			{
				turn = !turn;
				//board.FlipBoard();
			}
		}
		else {
			gameStatus = 0;
			SelectTile(row, column);
			return;
		}

		board.RemovePossibleTiles();
		gameStatus = 0;
	}
	
}