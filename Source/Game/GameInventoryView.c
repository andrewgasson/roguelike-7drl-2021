#include "Game/View.h"

#include "Game/Creature.h"
#include "Game/Handle.h"
#include "Game/Input.h"
#include "Game/Inventory.h"
#include "Game/Item.h"
#include "Raylib/terminal.h"
#include "Raylib/terminaldraw.h"
#include "Raylib/terminalgui.h"
#include "Raylib/terminalwrite.h"

static void OnOpenView(void);
static void OnCloseView(void);
static void OnControlView(void);
static void OnRenderView(void);

const View VIEW_GAME_INVENTORY = {
	.Open = OnOpenView,
	.Close = OnCloseView,
	.Control = OnControlView,
	.Render = OnRenderView,
	.requireGameWorldRender = false
};

static void OnOpenView(void)
{
	// Do nothing
}

static void OnCloseView(void)
{
	// Do nothing
}

static void OnControlView(void)
{
	if (IsInputActive(INPUT_UI_CANCEL))
		PopView();
}

static void OnRenderView(void)
{
	int i;
	Handle inventory;

	inventory = GetCreatureInventory(GetCreatureProtagonist());

	SetTerminalCursorWrap(false, false);
	SetTerminalCursorXY(0, 0);
	SetTerminalWriteBackPaint(BLACK);
	SetTerminalWriteForePaint(WHITE);

	for (i = 0; i < MAX_INVENTORY_ITEM_QUANTITY; i++) {
		ItemPrefab item;

		item = GetInventoryItemAtIndex(inventory, i);

		if (item != ITEM_PREFAB_NONE) {
			WriteTerminalText(GetItemName(item));
			MoveTerminalCursorNextLine();
			WriteTerminalText(GetItemDescription(item));
			MoveTerminalCursorNextLine();
			MoveTerminalCursorNextLine();
		}
	}
}
