#include "Game/Dungeon.h"

#include "Game/Creature.h"
#include "Game/Door.h"
#include "Game/Handle.h"
#include "Game/Sprite.h"
#include "Raylib/terminal.h"

void GenerateBasicDungeon(void)
{
	static const TerminalTile enemyTile = { .background = ALPHA_BLACK, .foreground = RED, .symbol = 'w' };
	Handle enemy;
	int startPosX;
	int startPosY;

	startPosX = GetTerminalWidth() / 2;
	startPosY = GetTerminalHeight() / 2;

	// Spawn maximum amount of enemies
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

	// If there is a non-protagonist creature at our starting position, 
	// destroy it
	SetCreaturePosition(GetCreatureProtagonist(), (Vector2) { -1, -1 });
	enemy = GetCreatureAtPosition((Vector2) { startPosX, startPosY });

	if (IsCreatureValid(enemy))
		DestroyCreature(enemy);

	SetCreaturePosition(GetCreatureProtagonist(), (Vector2) { startPosX, startPosY });

	// Spawn door (DEMO)
	{
		Handle door;
		Vector2 doorPosition;
	
		door = SpawnDoor();
		doorPosition = GetCreaturePosition(GetCreatureProtagonist());
		doorPosition.y--;
		SetDoorPosition(door, doorPosition);
	}
}

void GenerateCaveDungeon(void)
{
	//
}
