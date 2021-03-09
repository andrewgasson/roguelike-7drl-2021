#include "Game/Game.h"

#include "Game/Compass.h"
#include "Game/Creature.h"
#include "Game/Handle.h"
#include "Game/Sprite.h"
#include "Raylib/raylib.h"
#include "Raylib/terminal.h"

void InitGame(void)
{
	Handle player;
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
