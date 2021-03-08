#include "Game/Game.h"

#include "Game/Compass.h"
#include "Game/Creature.h"
#include "Game/Handle.h"
#include "Game/Sprite.h"
#include "Raylib/raylib.h"
#include "Raylib/raymath.h"
#include "Raylib/terminal.h"

static void ProtagonistWalk(Compass direction)
{
	Vector2 destination;
	Handle protagonist;
	Handle obstacle;

	protagonist = GetCreatureProtagonist();
	destination = Vector2Add(GetCreaturePosition(protagonist), CompassToVector2(direction));
	obstacle = GetCreatureAtPosition(destination);

	if (IsCreatureValid(obstacle)) {
		int obstacleHealth;

		obstacleHealth = GetCreatureStat(obstacle, CREATURE_STAT_HEALTH);
		obstacleHealth--;
		
		if (obstacleHealth < 0) {
			TraceLog(LOG_INFO, "GAME: Player demolished creature!");
			DestroyCreature(obstacle);
		} else {
			SetCreatureStat(obstacle, CREATURE_STAT_HEALTH, obstacleHealth);
		}
	} else {
		CreatureWalk(protagonist, direction);
	}
}

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
	SetCreatureStat(enemy, CREATURE_STAT_HEALTH, 1);
	SetCreatureProtagonist(player);
}

void UpdateGame(void)
{
	if (IsKeyDown(KEY_UP)) {
		ProtagonistWalk(COMPASS_NORTH);
	} else if (IsKeyDown(KEY_RIGHT)) {
		ProtagonistWalk(COMPASS_EAST);
	} else if (IsKeyDown(KEY_DOWN)) {
		ProtagonistWalk(COMPASS_SOUTH);
	} else if (IsKeyDown(KEY_LEFT)) {
		ProtagonistWalk(COMPASS_WEST);
	}
}

void RenderGame(void)
{
	ClearTerminal();
	RenderSprites();
}
