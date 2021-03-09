#include "Game/Creature.h"

#include "Game/Sprite.h"
#include "Raylib/raymath.h"
#include <stdlib.h> // for NULL

static void CacheActiveCreatures(int *outLength, Handle *outHandles[]);

static int creatureCapacity;
static int creatureCount;
static int creatureLowestFree;
static Handle creatureProtagonist;
static struct {
	bool reserved;
	unsigned int version;
} *creatureStatus;
static struct {
	Vector2 position;
	Handle sprite;
	int stats[CREATURE_STAT__LENGTH];
} *creatureData;

void InitCreatures(int capacity)
{
	int i;

	if (capacity < 1)
		capacity = 1;

	creatureStatus = MemAlloc(capacity * sizeof(*creatureStatus));
	creatureData = MemAlloc(capacity * sizeof(*creatureData));

	// CRASH: Allocation failure. Note, if we run out of paging file space 
	// it will hard crash before this, and probably with an ambiguous error
	if (!creatureStatus || !creatureData) {
		TraceLog(LOG_ERROR, TextFormat("CREATURE: Failed to allocate module to a capacity of %d", capacity));
		return;
	}

	creatureCapacity = capacity;

	for (i = 0; i < creatureCapacity; i++)
		creatureStatus[i].reserved = false;
	
	for (i = 0; i < creatureCapacity; i++)
		creatureData[i].sprite = NULL_HANDLE;

	creatureCount = 0;
	creatureLowestFree = 0;
	TraceLog(LOG_INFO, TextFormat("CREATURE: Initialized successfully (capacity: %d)", creatureCapacity));
}

inline int MaxCreatures(void)
{
	return creatureCapacity;
}

inline bool IsCreatureValid(Handle creature)
{
	return !IsHandleNull(creature)
		&& creatureStatus[creature.index].reserved
		&& creatureStatus[creature.index].version == creature.version;
}

Handle SpawnCreature(void)
{
	int i;

	for (i = creatureLowestFree; i < creatureCapacity; i++) {
		if (!creatureStatus[i].reserved) {
			int j;
			Handle handle;

			// Update instance status
			creatureStatus[i].reserved = true;
			creatureStatus[i].version++;

			// Make handle
			handle.version = creatureStatus[i].version;
			handle.index = i;

			// Update module status
			creatureCount++;
			creatureLowestFree = i + 1;

			// Prepare instance
			creatureData[i].position.x = 0;
			creatureData[i].position.y = 0;
			creatureData[i].sprite = SpawnSprite();

			for (j = 0; j < CREATURE_STAT__LENGTH; j++)
				creatureData[i].stats[j] = 0;

			return handle;
		}
	}

	return NULL_HANDLE;
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

void CreatureAttack(Handle creature, Compass direction)
{
	Handle obstacle;
	Vector2 destination;

	destination = Vector2Add(GetCreaturePosition(creature), CompassToVector2(direction));
	obstacle = GetCreatureAtPosition(destination);

	if (IsCreatureValid(obstacle)) {
		int damage;
		int health;

		damage = GetRandomValue(1, 6);
		health = GetCreatureStat(obstacle, CREATURE_STAT_HEALTH);
		health -= damage;
		SetCreatureStat(obstacle, CREATURE_STAT_HEALTH, health);

		if (IsCreatureProtagonist(creature))
			TraceLog(LOG_INFO, TextFormat("CREATURE: Protagonist dealt %d damage to creature", damage));

		if (health < 0) {
			if (IsCreatureProtagonist(creature))
				TraceLog(LOG_INFO, "CREATURE: Protagonist killed a creature!");

			DestroyCreature(obstacle);
		}
	}
}

void CreatureWalk(Handle creature, Compass direction)
{
	Handle obstacle;
	Vector2 destination;

	destination = Vector2Add(GetCreaturePosition(creature), CompassToVector2(direction));
	obstacle = GetCreatureAtPosition(destination);

	if (IsCreatureValid(obstacle)) {
		TraceLog(LOG_INFO, "CREATURE: Colliding with obstacle!");
		return;
	}

	SetCreaturePosition(creature, destination);
}

// This is not an effecient function. However, it should really only be called 
// for the protagonist.
void CreatureWalkOrInteract(Handle creature, Compass direction)
{
	Vector2 destination;
	Handle obstacle;

	destination = Vector2Add(GetCreaturePosition(creature), CompassToVector2(direction));
	obstacle = GetCreatureAtPosition(destination);

	if (IsCreatureValid(obstacle))
		CreatureAttack(creature, direction);
	else
		CreatureWalk(creature, direction);
}

Handle GetCreatureAtPosition(Vector2 position)
{
	int i;
	int length;
	Handle found;
	Handle *cache;

	CacheActiveCreatures(&length, &cache);

	if (!cache)
		return NULL_HANDLE;

	found = NULL_HANDLE;

	for (i = 0; i < length; i++) {
		if (creatureData[cache[i].index].position.x == position.x
		&&  creatureData[cache[i].index].position.y == position.y) {
			found = cache[i];
			break;
		}
	}

	MemFree(cache);
	return found;
}

inline Vector2 GetCreaturePosition(Handle creature)
{
	return creatureData[creature.index].position;
}

inline Handle GetCreatureProtagonist(void)
{
	return creatureProtagonist;
}

inline Handle GetCreatureSprite(Handle creature)
{
	return creatureData[creature.index].sprite;
}

inline int GetCreatureStat(Handle creature, CreatureStat stat)
{
	return creatureData[creature.index].stats[stat];
}

inline bool IsCreatureProtagonist(Handle creature)
{
	return IsCreatureValid(creatureProtagonist)
		&& AreHandlesEqual(creature, creatureProtagonist);
}

inline void SetCreaturePosition(Handle creature, Vector2 position)
{
	creatureData[creature.index].position = position;
	
	if (IsSpriteValid(creatureData[creature.index].sprite))
		SetSpritePosition(creatureData[creature.index].sprite, position);
}

inline void SetCreatureProtagonist(Handle creature)
{
	creatureProtagonist = creature;
}

inline void SetCreatureStat(Handle creature, CreatureStat stat, int value)
{
	creatureData[creature.index].stats[stat] = value;
}

static void CacheActiveCreatures(int *outLength, Handle *outHandles[])
{
	int i;
	int j;

	// EXIT: There are no creatures
	if (creatureCount == 0) {
		*outLength = 0;
		*outHandles = NULL;
		return;
	}

	*outLength = 0;
	*outHandles = MemAlloc(creatureCount * sizeof(**outHandles));

	// CRASH: Allocation failure
	if (!*outHandles) {
		TraceLog(LOG_ERROR, TextFormat("CREATURE: Failed to allocate cache (size: %d)", creatureCount));
		return;
	}

	for (j = 0, i = 0; i < creatureCapacity; i++) {
		if (creatureStatus[i].reserved) {
			(*outHandles)[j].index = i;
			(*outHandles)[j].version = creatureStatus[i].version;
			j++;

			// BREAK: Leave early if we've found all the instances.
			if (j == creatureCount)
				break;
		}
	}

	*outLength = j;
}
