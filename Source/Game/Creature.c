#include "Game/Creature.h"

#include "Game/Sprite.h"
#include "Raylib/raymath.h"
#include <stdlib.h> // for NULL

// Spawned creatures have a minimum version of 1, so a version of 0 is NULL.
#define NULL_CREATURE (Handle) { 0 }

static int creatureCapacity;
static int creatureCount;
static int creatureLowestFree;
static struct {
	bool reserved;
	unsigned int version;
} *creatureStatus;
static struct {
	Vector2 position;
	Handle sprite;
} *creatureData;
static Handle creatureProtagonist;

void InitCreatures(int capacity)
{
	if (capacity < 1)
		capacity = 1;

	creatureStatus = MemAlloc(capacity * sizeof(*creatureStatus));
	creatureData = MemAlloc(capacity * sizeof(*creatureData));

	// CRASH: Allocation failure. Note, if we run out of paging file space 
	// it will hard crash without any clear errors.
	if (!creatureStatus || !creatureData) {
		TraceLog(LOG_ERROR, TextFormat("CREATURE: Failed to allocate module to a capacity of %d", capacity));
		return;
	}

	creatureCapacity = capacity;
	DestroyAllCreatures();
	TraceLog(LOG_INFO, TextFormat("CREATURE: Initialized successfully (capacity: %d)", creatureCapacity));
}

inline int MaxCreatures(void)
{
	return creatureCapacity;
}

inline bool IsCreatureValid(Handle creature)
{
	return creature.index < creatureCapacity
		&& creatureStatus[creature.index].reserved
		&& creatureStatus[creature.index].version == creature.version;
}

Handle SpawnCreature(void)
{
	int i;

	for (i = creatureLowestFree; i < creatureCapacity; i++) {
		if (!creatureStatus[i].reserved) {
			// Update instance status
			creatureStatus[i].reserved = true;
			creatureStatus[i].version++;

			// Update module status
			creatureCount++;
			creatureLowestFree = i + 1;

			// Prepare instance
			creatureData[i].position.x = 0;
			creatureData[i].position.y = 0;
			creatureData[i].sprite = SpawnSprite();

			return (Handle) {
				.version = creatureStatus[i].version, 
				.index = i
			};
		}
	}

	return NULL_CREATURE;
}

void DestroyCreature(Handle creature)
{
	creatureStatus[creature.index].reserved = false;

	if (IsSpriteValid(creatureData[creature.index].sprite))
		DestroySprite(creatureData[creature.index].sprite);

	creatureCount--;

	if (creature.index < creatureLowestFree)
		creatureLowestFree = creature.index;
}

void DestroyAllCreatures(void)
{
	int i;

	for (i = 0; i < creatureCapacity; i++)
		creatureStatus[i].reserved = false;

	for (i = 0; i < creatureCapacity; i++) {
		if (IsSpriteValid(creatureData[i].sprite))
			DestroySprite(creatureData[i].sprite);
	}

	creatureCount = 0;
	creatureLowestFree = 0;
}

inline int CountCreatures(void)
{
	return creatureCapacity;
}

inline Handle GetCreatureProtagonist(void)
{
	return creatureProtagonist;
}

inline bool IsCreatureProtagonist(Handle creature)
{
	return IsCreatureValid(creatureProtagonist)
		&& AreHandlesEqual(creature, creatureProtagonist);
}

inline void SetCreatureProtagonist(Handle creature)
{
	creatureProtagonist = creature;
}

inline Vector2 GetCreaturePosition(Handle creature)
{
	return creatureData[creature.index].position;
}

inline Handle GetCreatureSprite(Handle creature)
{
	return creatureData[creature.index].sprite;
}

inline void SetCreaturePosition(Handle creature, Vector2 position)
{
	creatureData[creature.index].position = position;
	
	if (IsSpriteValid(creatureData[creature.index].sprite))
		SetSpritePosition(creatureData[creature.index].sprite, position);
}

void CreatureWalk(Handle creature, Compass direction)
{
	Vector2 destination;

	destination = Vector2Add(GetCreaturePosition(creature), CompassToVector2(direction));

	SetCreaturePosition(creature, destination);
}
