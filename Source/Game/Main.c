#include "Game/Main.h"

#include "Game/Actor.h"
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
#define ACTOR_CAPACITY (CREATURE_CAPACITY * CONTAINER_CAPACITY)
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

	// Initialize modules (order matters only in regards to memory locality, 
	// otherwise, because modules are relational, they do not depend on 
	// each other for initialization)
	InitInput();
	InitTerrain(GetTerminalWidth(), GetTerminalHeight(), 1);
	InitItemPrefabs();
	InitActors(ACTOR_CAPACITY);
	InitContainers(CONTAINER_CAPACITY);
	InitCreatures(CREATURE_CAPACITY);
	InitDoors(DOOR_CAPACITY);
	InitInventories(INVENTORY_CAPACITY);
	InitSprites(SPRITE_CAPACITY);

	// Start engine loop
	SetView(&VIEW_MAIN_MENU);
	appRunning = true;

	while (!WindowShouldClose() && appRunning) {
		UpdateInput();
		ControlView();
		ClearTerminal();

		if (ShouldProcessGameActors()) {
			// TODO: Any view that requests a pause turn process should be a block (sort of the opposite of world render)
			// If it is the player's turn, skip,
			// else if there are no actors to process, process
			// the round
			// else process up to the maximum actors
		}

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

	// Let the platform cleanup, yet ensure at least the window or app 
	// instance is closed
	CloseWindow();
	return 0;
}
