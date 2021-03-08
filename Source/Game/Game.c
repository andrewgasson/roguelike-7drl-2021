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
	TerminalTile playerTile;
	TerminalTile enemyTile;

	playerTile.background = ALPHA_BLACK;
	playerTile.foreground = WHITE;
	playerTile.symbol = '@';

	enemyTile.background = ALPHA_BLACK;
	enemyTile.foreground = RED;
	enemyTile.symbol = 'w';

	InitSprites(16);
	InitCreatures(16);

	// Spawn player
	{
		player = SpawnCreature();

		if (IsCreatureValid(player)) {
			Vector2 position;

			position.x = GetTerminalWidth() / 2;
			position.y = GetTerminalHeight() / 2;

			SetSpriteTile(GetCreatureSprite(player), playerTile);
			SetCreaturePosition(player, position);
			SetCreatureProtagonist(player);
		} else {
			TraceLog(LOG_ERROR, "GAME: Player creature is invalid.");
			return;
		}
	}

	// Spawn enemies
	{
		Handle enemy;

		while (IsCreatureValid((enemy = SpawnCreature()))) {
			Vector2 position;
			int health;

			position.x = GetRandomValue(1, GetTerminalWidth() - 2);
			position.y = GetRandomValue(1, GetTerminalHeight() - 2);
			health = 12 + GetRandomValue(2, 12);

			SetSpriteTile(GetCreatureSprite(enemy), enemyTile);
			SetCreaturePosition(enemy, position);
			SetCreatureStat(enemy, CREATURE_STAT_HEALTH, health);
		}
	}
	
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
