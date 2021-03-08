#include "Game/Game.h"

#include "Raylib/raylib.h"
#include "Raylib/raymath.h"
#include "Raylib/terminal.h"

#define VECTOR2_NORTH CLITERAL(Vector2){  0, -1 }
#define VECTOR2_EAST  CLITERAL(Vector2){  1,  0 }
#define VECTOR2_SOUTH CLITERAL(Vector2){  0,  1 }
#define VECTOR2_WEST  CLITERAL(Vector2){ -1,  0 }

typedef struct Creature {
	Vector2 position;
	TerminalTile sprite;
} Creature;

static Creature player;

void InitGame(void)
{
	player.position.x = 0;
	player.position.y = 0;
	player.sprite.background = ALPHA_BLACK;
	player.sprite.foreground = WHITE;
	player.sprite.symbol = '@';
}

void UpdateGame(void)
{
	if (IsKeyDown(KEY_UP)) {
		player.position = Vector2Add(player.position, VECTOR2_NORTH);
	} else if (IsKeyDown(KEY_RIGHT)) {
		player.position = Vector2Add(player.position, VECTOR2_EAST);
	} else if (IsKeyDown(KEY_DOWN)) {
		player.position = Vector2Add(player.position, VECTOR2_SOUTH);
	} else if (IsKeyDown(KEY_LEFT)) {
		player.position = Vector2Add(player.position, VECTOR2_WEST);
	}
}

void RenderGame(void)
{
	ClearTerminal();

	if (IsWithinTerminalV(player.position))
		SetTerminalTileV(player.position, player.sprite);
}
