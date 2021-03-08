#include "Game/Game.h"

#include "Game/Compass.h"
#include "Game/Creature.h"
#include "Game/Handle.h"
#include "Raylib/raylib.h"
#include "Raylib/raymath.h"
#include "Raylib/terminal.h"

#define VECTOR2_NORTH CLITERAL(Vector2){  0, -1 }
#define VECTOR2_EAST  CLITERAL(Vector2){  1,  0 }
#define VECTOR2_SOUTH CLITERAL(Vector2){  0,  1 }
#define VECTOR2_WEST  CLITERAL(Vector2){ -1,  0 }

void InitGame(void)
{
	Handle player;
	TerminalTile playerSprite;

	InitCreatures(16);

	player = SpawnCreature();

	if (!IsCreatureValid(player)) {
		TraceLog(LOG_ERROR, "GAME: Player creature is invalid.");
		return;
	}

	playerSprite.background = ALPHA_BLACK;
	playerSprite.foreground = WHITE;
	playerSprite.symbol = '@';
	SetCreatureSprite(player, playerSprite);
	SetCreatureProtagonist(player);
}

void UpdateGame(void)
{
	if (IsKeyDown(KEY_UP)) {
		CreatureWalk(GetCreatureProtagonist(), COMPASS_NORTH);
	} else if (IsKeyDown(KEY_RIGHT)) {
		CreatureWalk(GetCreatureProtagonist(), COMPASS_EAST);
	} else if (IsKeyDown(KEY_DOWN)) {
		CreatureWalk(GetCreatureProtagonist(), COMPASS_SOUTH);
	} else if (IsKeyDown(KEY_LEFT)) {
		CreatureWalk(GetCreatureProtagonist(), COMPASS_WEST);
	}
}

void RenderGame(void)
{
	Handle protagonist;

	ClearTerminal();

	protagonist = GetCreatureProtagonist();

	if (IsCreatureValid(protagonist) && IsWithinTerminalV(GetCreaturePosition(protagonist)))
		SetTerminalTileV(GetCreaturePosition(protagonist), GetCreatureSprite(protagonist));
}
