#include "Game/Game.h"

#include "Game/Compass.h"
#include "Game/Creature.h"
#include "Game/Handle.h"
#include "Game/Sprite.h"
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
	Handle enemy;
	TerminalTile playerSprite;
	TerminalTile enemySprite;

	playerSprite.background = ALPHA_BLACK;
	playerSprite.foreground = WHITE;
	playerSprite.symbol = '@';

	enemySprite.background = ALPHA_BLACK;
	enemySprite.foreground = RED;
	enemySprite.symbol = 'E';

	InitSprites(32);
	InitCreatures(16);

	player = SpawnCreature();
	enemy = SpawnCreature();

	if (!IsCreatureValid(player)) {
		TraceLog(LOG_ERROR, "GAME: Player creature is invalid.");
		return;
	}

	if (IsSpriteValid(GetCreatureSprite(player)))
		SetSpriteTile(GetCreatureSprite(player), playerSprite);

	if (IsSpriteValid(GetCreatureSprite(enemy)))
		SetSpriteTile(GetCreatureSprite(enemy), enemySprite);

	SetCreaturePosition(enemy, (Vector2) { GetTerminalWidth() / 2, GetTerminalHeight() / 2 });
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
	ClearTerminal();
	RenderSprites();
}
