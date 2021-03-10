#ifndef GAME_H
#define GAME_H

#include "Game/Handle.h"

void NewGame(void);
void LoadGame(const char *fileName);
void SaveGame(const char *fileName);
Handle SpawnProtagonist(void);

#endif // GAME_H
