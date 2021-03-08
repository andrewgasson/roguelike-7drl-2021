#include "Game/Game.h"
#include "Raylib/raylib.h"
#include "Raylib/terminal.h"

/*
static void RainbowTerminal(void)
{
	int i;
	int length;
	TerminalTile *tiles;
	
	length = GetTerminalWidth() * GetTerminalHeight();
	tiles = GetTerminalTileBuffer();

	for (i = 0; i < length; i++) {
		Color background;
		Color foreground;
		char symbol;

		background.r = 128 + GetRandomValue(0, 127);
		background.g = 128 + GetRandomValue(0, 127);
		background.b = 128 + GetRandomValue(0, 127);
		background.a = 255;

		foreground.r = GetRandomValue(0, 128);
		foreground.g = GetRandomValue(0, 128);
		foreground.b = GetRandomValue(0, 128);
		foreground.a = 128;

		symbol = GetRandomValue('A', 'z');

		tiles[i].background = background;
		tiles[i].foreground = foreground;
		tiles[i].symbol = symbol;
	}
}
*/

int main(int argc, char *argv[])
{
	(void) argc; // Unused
	(void) argv; // Unused

	// Setup raylib
	SetConfigFlags(FLAG_VSYNC_HINT);
	InitWindow(640, 480, "7DRL 2021");
	SetTargetFPS(30);

	// Setup terminal
	InitTerminal(80, 26);
	LoadTerminalFont("..\\Asset\\VGA9x16.png", 1);
	SetWindowSize(GetTerminalScreenWidth(), GetTerminalScreenHeight());
	
	// Stop immediate seizures
	BeginDrawing();
		ClearBackground(BLACK);
	EndDrawing();
	BeginDrawing();
		ClearBackground(BLACK);
	EndDrawing();

	// Start game loop
	InitGame();

	while (!WindowShouldClose()) {
		UpdateGame();
		RenderGame();
		BeginDrawing();
			ClearBackground(BLACK);
			DrawTerminal();
		EndDrawing();
	}

	CloseWindow();
	return 0;
}
