#include "Game/Game.h"

#include "Game/Creature.h"
#include "Game/Dungeon.h"
#include "Game/Handle.h"
#include "Game/Sprite.h"
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

Handle SpawnProtagonist(void)
{
	static const TerminalTile playerTile = { .background = ALPHA_BLACK, .foreground = WHITE, .symbol = '@' };
	Handle protagonist;

	protagonist = GetCreatureProtagonist();

	if (IsCreatureValid(protagonist))
		DestroyCreature(protagonist);

	protagonist = SpawnCreature();

	// CRASH: Protagonist failed to spawn
	if (!IsCreatureValid(protagonist)) {
		TraceLog(LOG_ERROR, "GAME: Failed to spawn a protagonist");
		return NULL_HANDLE;
	}

	SetCreatureProtagonist(protagonist);
	SetSpriteTile(GetCreatureSprite(protagonist), playerTile);

	return protagonist;
}
