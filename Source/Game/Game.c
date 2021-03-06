#include "Game/Game.h"

#include "Game/Creature.h"
#include "Game/Dungeon.h"
#include "Game/Handle.h"
#include "Game/Sprite.h"
#include "Game/View.h"
#include "Raylib/raylib.h"
#include "Raylib/terminal.h"

void NewGame(void)
{
	// Cleanup
	DestroyAllCreatures();

	// Setup
	SpawnProtagonist();
	GenerateBasicDungeon();
}

void LoadGame(const char *fileName)
{
	// TODO
}

void SaveGame(const char *fileName)
{
	// TODO
}

void GameOver(void)
{
	// TODO: Temporary
	SetView(&VIEW_MAIN_MENU);
}

Handle SpawnProtagonist(void)
{
	static const TerminalTile playerTile = { .background = ALPHA_BLACK, .foreground = WHITE, .symbol = '@' };
	Handle protagonist;

	// Destroy the previous protagonist
	protagonist = GetCreatureProtagonist();

	if (IsCreatureValid(protagonist))
		DestroyCreature(protagonist);

	protagonist = SpawnCreature();

	// CRASH: Protagonist failed to spawn
	if (!IsCreatureValid(protagonist)) {
		TraceLog(LOG_ERROR, "GAME: Failed to spawn the protagonist");
		return NULL_HANDLE;
	}

	// Initialize protagonist
	SetCreatureProtagonist(protagonist);
	SetCreatureStat(protagonist, CREATURE_STAT_LEVEL, 1);
	SetSpriteTile(GetCreatureSprite(protagonist), playerTile);

	return protagonist;
}
