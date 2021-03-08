#include "Game/Game.h"

#include "Game/Compass.h"
#include "Game/Creature.h"
#include "Game/Handle.h"
#include "Game/Sprite.h"
#include "Raylib/raylib.h"
#include "Raylib/raymath.h"
#include "Raylib/terminal.h"

#define GAME_INPUT_COOLDOWN 2

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
	SetCreatureStat(enemy, CREATURE_STAT_HEALTH, 12 + GetRandomValue(2, 12));
	SetCreatureProtagonist(player);
}

void UpdateGame(void)
{
	static int inputTimer = 0;

	// TEMP: Ideally keys happen immediately, or until held down for x, 
	// then every y. This temporary hack makes it easier to see each step.
	if (inputTimer > 0) {
		inputTimer--;
		return;
	}

	if (IsKeyDown(KEY_UP)) {
		CreatureWalkOrInteract(GetCreatureProtagonist(), COMPASS_NORTH);
		inputTimer = GAME_INPUT_COOLDOWN;
	} else if (IsKeyDown(KEY_RIGHT)) {
		CreatureWalkOrInteract(GetCreatureProtagonist(), COMPASS_EAST);
		inputTimer = GAME_INPUT_COOLDOWN;
	} else if (IsKeyDown(KEY_DOWN)) {
		CreatureWalkOrInteract(GetCreatureProtagonist(), COMPASS_SOUTH);
		inputTimer = GAME_INPUT_COOLDOWN;
	} else if (IsKeyDown(KEY_LEFT)) {
		CreatureWalkOrInteract(GetCreatureProtagonist(), COMPASS_WEST);
		inputTimer = GAME_INPUT_COOLDOWN;
	}
}

void RenderGame(void)
{
	ClearTerminal();
	RenderSprites();
}
