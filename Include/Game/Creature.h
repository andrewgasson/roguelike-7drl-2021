#ifndef GAME_CREATURE_H
#define GAME_CREATURE_H

typedef enum {
	CREATURE_STAT_HEALTH,
	// Size
	CREATURE_STAT__LENGTH
} CreatureStat;

#include "Game/Compass.h"
#include "Game/Handle.h"
#include "Raylib/raylib.h"
#include "Raylib/terminal.h"

void InitCreatures(int capacity);
int MaxCreatures(void);

bool IsCreatureValid(Handle creature);
Handle SpawnCreature(void);
void DestroyCreature(Handle creature);
void DestroyAllCreatures(void);
void DestroyAllButProtagonistCreatures(void);
int CountCreatures(void);

void CreatureAttack(Handle creature, Compass direction);
void CreatureWalk(Handle creature, Compass direction);
void CreatureWalkOrInteract(Handle creature, Compass direction);
Handle GetCreatureAtPosition(Vector2 position);
Vector2 GetCreaturePosition(Handle creature);
Handle GetCreatureProtagonist(void);
Handle GetCreatureSprite(Handle creature); // Owned return
int GetCreatureStat(Handle creature, CreatureStat stat);
bool IsCreatureProtagonist(Handle creature);
void SetCreaturePosition(Handle creature, Vector2 position);
void SetCreatureProtagonist(Handle creature);
void SetCreatureStat(Handle creature, CreatureStat stat, int value);

#endif // GAME_CREATURE_H
