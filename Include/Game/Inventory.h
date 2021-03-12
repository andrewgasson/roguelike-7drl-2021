#ifndef GAME_INVENTORY_H
#define GAME_INVENTORY_H

#include "Game/Handle.h"
#include "Game/Item.h"
#include "Raylib/raylib.h"

#define MAX_INVENTORY_ITEM_QUANTITY 32

void InitInventories(int capacity);
int MaxInventories(void);

bool IsInventoryValid(Handle inventory);
Handle SpawnInventory(void);
void DestroyInventory(Handle inventory);
void DestroyAllInventories(void);
int CountInventories(void);

int AddInventoryItem(Handle inventory, ItemPrefab itemPrefab, int quantity);    // Returns the amount of prefabs added
int CountAllInventoryItems(Handle inventory);
int CountInventoryItem(Handle inventory, ItemPrefab itemPrefab);
int GetTotalInventoryPrice(Handle inventory);
float GetTotalInventoryWeight(Handle inventory);
bool IsInventoryEmpty(Handle inventory);
bool IsInventoryFull(Handle inventory);
int RemoveInventoryItem(Handle inventory, ItemPrefab itemPrefab, int quantity); // Returns the amount of prefabs removed

#endif // GAME_INVENTORY_H
