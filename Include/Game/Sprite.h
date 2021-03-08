#ifndef GAME_SPRITE_H
#define GAME_SPRITE_H

#include "Game/Handle.h"
#include "Raylib/raylib.h"
#include "Raylib/terminal.h"

void InitSprites(int capacity);
int MaxSprites(void);

bool IsSpriteValid(Handle sprite);
Handle SpawnSprite(void);
void DestroySprite(Handle sprite);
void DestroyAllSprites(void);
int CountSprites(void);

bool GetSpriteEnabled(Handle sprite);
Vector2 GetSpritePosition(Handle sprite);
TerminalTile GetSpriteTile(Handle sprite);
void SetSpriteEnabled(Handle sprite, bool enabled);
void SetSpritePosition(Handle sprite, Vector2 position);
void SetSpriteTile(Handle sprite, TerminalTile tile);

void RenderSprites(void);

#endif // GAME_SPRITE_H
