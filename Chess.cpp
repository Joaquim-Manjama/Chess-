#include <iostream>
#include <raylib.h>
#include "game.h"

// Main Game function
int main()
{
	// Initialize the Window
	InitWindow(800, 800, "Chess");
	SetTargetFPS(30);

	Game game = Game();
	game.PrintBoard();
	
	// Game Loop
	while (WindowShouldClose() == false)
	{
		//EVENT HANDLING
		if (IsMouseButtonPressed(0))
		{
			int row = GetMouseY() / 100;
			int column = GetMouseX() / 100;
			game.SelectTile(row, column);
		}

		//UPDATE
		
		//DRAWING
		BeginDrawing();
		ClearBackground(RAYWHITE);
		game.Draw(GetMouseY() / 100, GetMouseX() / 100);
		EndDrawing();
	}
			
	// End of Game
	CloseWindow();
	return 0;
}