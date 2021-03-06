#ifndef GAME_DOOR_H
#define GAME_DOOR_H

#include "Game/Handle.h"
#include "Raylib/raylib.h"
#include "Raylib/terminal.h"

void InitDoors(int capacity);
int MaxDoors(void);

bool IsDoorValid(Handle door);
Handle SpawnDoor(void);
void DestroyDoor(Handle door);
void DestroyAllDoors(void);
int CountDoors(void);

Handle GetDoorAtPosition(Vector2 position);
TerminalTile GetDoorClosedTile(Handle door);
TerminalTile GetDoorOpenedTile(Handle door);
Vector2 GetDoorPosition(Handle door);
bool IsDoorOpened(Handle door);
void SetDoorClosedTile(Handle door, TerminalTile closedTile);
void SetDoorOpened(Handle door, bool opened);
void SetDoorOpenedTile(Handle door, TerminalTile openedTile);
void SetDoorPosition(Handle door, Vector2 position);

#endif // GAME_DOOR_H
