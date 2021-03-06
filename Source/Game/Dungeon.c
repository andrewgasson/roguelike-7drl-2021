#include "Game/Dungeon.h"

#include "Game/Container.h"
#include "Game/Creature.h"
#include "Game/Door.h"
#include "Game/Handle.h"
#include "Game/Inventory.h"
#include "Game/Item.h"
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
		doorPosition.y -= 2;
		SetDoorPosition(door, doorPosition);
	}

	// Spawn container with item (DEMO)
	{
		Handle container;
		Vector2 containerPosition;

		container = SpawnContainer(CONTAINER_TYPE_LOOT);
		containerPosition = GetCreaturePosition(GetCreatureProtagonist());
		containerPosition.x += 2;
		containerPosition.y += 1;
		SetContainerPosition(container, containerPosition);
		AddInventoryItem(GetContainerInventory(container), ITEM_PREFAB_WEAP_IRON_LONGSWORD, 1);
	}
}

void GenerateCaveDungeon(void)
{
	//
}
