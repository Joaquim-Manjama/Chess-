#pragma once
#include <string>
#include <vector>
#include "board.h";

class Game 
{
public:
	Game();
	void Draw(int row, int column);
	void Update();
	void PrintBoard();
	void SelectTile(int row, int column);
	std::vector<std::string> gameStatuses;
	int gameStatus;
	bool turn;
private:
	Board board;
};