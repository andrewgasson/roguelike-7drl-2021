#ifndef GAME_CREATURE_H
#define GAME_CREATURE_H

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
int CountCreatures(void);

Handle GetCreatureProtagonist(void);
bool IsCreatureProtagonist(Handle creature);
void SetCreatureProtagonist(Handle creature);

Vector2 GetCreaturePosition(Handle creature);
TerminalTile GetCreatureSprite(Handle creature);

void SetCreaturePosition(Handle creature, Vector2 position);
void SetCreatureSprite(Handle creature, TerminalTile sprite);

void CreatureWalk(Handle creature, Compass direction);

#endif // GAME_CREATURE_H
