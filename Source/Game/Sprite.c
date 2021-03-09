#include "Game/Sprite.h"

#include "Raylib/raymath.h"
#include <stdlib.h> // for NULL

static int spriteCapacity;
static int spriteCount;
static int spriteLowestFree;
static struct {
	bool reserved;
	unsigned int version;
} *spriteStatus;
static struct {
	bool enabled;
	Vector2 position;
	TerminalTile tile;
} *spriteData;

void InitSprites(int capacity)
{
	if (capacity < 1)
		capacity = 1;

	spriteStatus = MemAlloc(capacity * sizeof(*spriteStatus));
	spriteData = MemAlloc(capacity * sizeof(*spriteData));

	// CRASH: Allocation failure. Note, if we run out of paging file space 
	// it will hard crash before this, and probably with an ambiguous error
	if (!spriteStatus || !spriteData) {
		TraceLog(LOG_ERROR, TextFormat("SPRITE: Failed to allocate module to a capacity of %d", capacity));
		return;
	}

	spriteCapacity = capacity;
	DestroyAllSprites();
	TraceLog(LOG_INFO, TextFormat("SPRITE: Initialized successfully (capacity: %d)", spriteCapacity));
}

inline int MaxSprites(void)
{
	return spriteCapacity;
}

inline bool IsSpriteValid(Handle sprite)
{
	return !IsHandleNull(sprite)
		&& spriteStatus[sprite.index].reserved
		&& spriteStatus[sprite.index].version == sprite.version;
}

Handle SpawnSprite(void)
{
	int i;

	for (i = spriteLowestFree; i < spriteCapacity; i++) {
		if (!spriteStatus[i].reserved) {
			Handle handle;

			// Update instance status
			spriteStatus[i].reserved = true;
			spriteStatus[i].version++;

			// Make handle
			handle.version = spriteStatus[i].version;
			handle.index = i;

			// Update module status
			spriteCount++;
			spriteLowestFree = i + 1;

			// Prepare instance
			spriteData[i].enabled = true;
			spriteData[i].position.x = 0;
			spriteData[i].position.y = 0;
			spriteData[i].tile.background = ALPHA_BLACK;
			spriteData[i].tile.foreground = DARKGRAY;
			spriteData[i].tile.symbol = '?';

			return handle;
		}
	}

	return NULL_HANDLE;
}

inline void DestroySprite(Handle sprite)
{
	spriteStatus[sprite.index].reserved = false;
	spriteCount--;

	if (sprite.index < spriteLowestFree)
		spriteLowestFree = sprite.index;
}

void DestroyAllSprites(void)
{
	int i;

	for (i = 0; i < spriteCapacity; i++)
		spriteStatus[i].reserved = false;

	spriteCount = 0;
	spriteLowestFree = 0;
}

inline int CountSprites(void)
{
	return spriteCount;
}

inline bool GetSpriteEnabled(Handle sprite)
{
	return spriteData[sprite.index].enabled;
}

inline Vector2 GetSpritePosition(Handle sprite)
{
	return spriteData[sprite.index].position;
}

inline TerminalTile GetSpriteTile(Handle sprite)
{
	return spriteData[sprite.index].tile;
}

inline void SetSpriteEnabled(Handle sprite, bool enabled)
{
	spriteData[sprite.index].enabled = enabled;
}

inline void SetSpritePosition(Handle sprite, Vector2 position)
{
	spriteData[sprite.index].position = position;
}

inline void SetSpriteTile(Handle sprite, TerminalTile tile)
{
	spriteData[sprite.index].tile = tile;
}

void RenderSprites(void)
{
	int i;
	int j;
	int cacheLength;
	Handle *cache;

	cacheLength = spriteCount;
	cache = MemAlloc(spriteCount * sizeof(*cache));

	// CRASH: Allocation failure
	if (!cache) {
		TraceLog(LOG_ERROR, TextFormat("SPRITE: Render failed to allocate a handle cache (size: %d)", spriteCount));
		return;
	}

	// Cache active
	for (j = 0, i = 0; i < spriteCapacity; i++) {
		if (spriteStatus[i].reserved) {
			cache[j].index = i;
			cache[j].version = spriteStatus[i].version;
			j++;

			// BREAK: Leave when we have found all active instances
			if (j == spriteCapacity)
				break;
		}
	}

	cacheLength = j;

	// Cull disabled
	for (j = 0, i = 0; i < cacheLength; i++) {
		if (spriteData[i].enabled) {
			cache[i] = cache[j];
			j++;
		}
	}

	cacheLength = j;

	// Cull out of bounds
	for (j = 0, i = 0; i < cacheLength; i++) {
		if (IsWithinTerminalV(spriteData[i].position)) {
			cache[j] = cache[i];
			j++;
		}
	}

	cacheLength = j;

	// Render to terminal
	for (i = 0; i < cacheLength; i++)
		SetTerminalTileV(spriteData[cache[i].index].position, spriteData[cache[i].index].tile);
}
