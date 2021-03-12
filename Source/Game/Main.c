#include "Game/Main.h"

#include "Game/Container.h"
#include "Game/Creature.h"
#include "Game/Door.h"
#include "Game/Game.h"
#include "Game/Input.h"
#include "Game/Inventory.h"
#include "Game/Item.h"
#include "Game/Sprite.h"
#include "Game/Terrain.h"
#include "Game/View.h"
#include "Raylib/raylib.h"
#include "Raylib/terminal.h"

#define CONTAINER_CAPACITY 32
#define CREATURE_CAPACITY 16
#define DOOR_CAPACITY 16
#define INVENTORY_CAPACITY (CREATURE_CAPACITY * CONTAINER_CAPACITY)
#define SPRITE_CAPACITY (CREATURE_CAPACITY * CONTAINER_CAPACITY * DOOR_CAPACITY)

static bool appRunning;

void QuitApplication(void)
{
	appRunning = false;
}

int main(int argc, char *argv[])
{
	(void) argc; // Unused
	(void) argv; // Unused

	// Setup raylib
	SetConfigFlags(FLAG_VSYNC_HINT);
	InitWindow(640, 480, "7DRL 2021");
	SetTargetFPS(30);
	SetExitKey(0);

	// Setup terminal
	InitTerminal(80, 26);
	LoadTerminalFont("..\\Asset\\VGA9x16.png", 1);
	SetWindowSize(GetTerminalScreenWidth(), GetTerminalScreenHeight());
	
	// Stop immediate seizures
	BeginDrawing();
		ClearBackground(BLACK);
	EndDrawing();
	BeginDrawing();
		ClearBackground(BLACK);
	EndDrawing();

	// Initialize modules
	InitInput();
	InitTerrain(GetTerminalWidth(), GetTerminalHeight(), 1);
	InitItemPrefabs();
	InitSprites(SPRITE_CAPACITY);
	InitInventories(INVENTORY_CAPACITY);
	InitContainers(CONTAINER_CAPACITY);
	InitDoors(DOOR_CAPACITY);
	InitCreatures(CREATURE_CAPACITY);

	// Start engine loop
	SetView(&VIEW_MAIN_MENU);
	appRunning = true;

	while (!WindowShouldClose() && appRunning) {
		UpdateInput();
		ControlView();
		ClearTerminal();

		if (ShouldRenderGameWorld()) {
			RenderTerrain(0);
			RenderSprites();
		}

		RenderViews();
		BeginDrawing();
			ClearBackground(BLACK);
			DrawTerminal();
		EndDrawing();
	}

	CloseWindow();
	return 0;
}
