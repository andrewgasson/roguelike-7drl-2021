#include "Game/View.h"

#include "Game/Compass.h"
#include "Game/Creature.h"
#include "Game/Input.h"
#include "Raylib/terminal.h"

static void OnOpenView(void);
static void OnCloseView(void);
static void OnControlView(void);
static void OnRenderView(void);

const View VIEW_GAME_DEFAULT = {
	.Open = OnOpenView,
	.Close = OnCloseView,
	.Control = OnControlView,
	.Render = OnRenderView,
	.requireGameWorldRender = true
};

static void OnOpenView(void)
{
	//
}

static void OnCloseView(void)
{
	//
}

static void OnControlView(void)
{
	if (IsInputActive(INPUT_UI_TOGGLE_PAUSE_MENU))
		PushView(&VIEW_GAME_PAUSED);
	else if (IsInputActive(INPUT_GAME_WALK_NORTH))
		CreatureWalkOrInteract(GetCreatureProtagonist(), COMPASS_NORTH);
	else if (IsInputActive(INPUT_GAME_WALK_EAST))
		CreatureWalkOrInteract(GetCreatureProtagonist(), COMPASS_EAST);
	else if (IsInputActive(INPUT_GAME_WALK_SOUTH))
		CreatureWalkOrInteract(GetCreatureProtagonist(), COMPASS_SOUTH);
	else if (IsInputActive(INPUT_GAME_WALK_WEST))
		CreatureWalkOrInteract(GetCreatureProtagonist(), COMPASS_WEST);
}

static void OnRenderView(void)
{
	// TODO: HUD
}
