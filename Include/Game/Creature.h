#ifndef GAME_CREATURE_H
#define GAME_CREATURE_H

#include "Game/Compass.h"
#include "Game/Handle.h"
#include "Raylib/raylib.h"
#include "Raylib/terminal.h"

// Sprite module must be initialized first.
void InitCreatures(int capacity);
int MaxCreatures(void);

bool IsCreatureValid(Handle creature);
Handle SpawnCreature(void);
void DestroyCreature(Handle creature);
void DestroyAllCreatures(void);
int CountCreatures(void);

void CreatureWalk(Handle creature, Compass direction);
Handle GetCreatureAtPosition(Vector2 position);
Vector2 GetCreaturePosition(Handle creature);
Handle GetCreatureProtagonist(void);
Handle GetCreatureSprite(Handle creature); // Owned return
bool IsCreatureProtagonist(Handle creature);
void SetCreaturePosition(Handle creature, Vector2 position);
void SetCreatureProtagonist(Handle creature);

#endif // GAME_CREATURE_H
