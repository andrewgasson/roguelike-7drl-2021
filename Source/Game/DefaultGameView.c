#include "Game/View.h"

#include "Game/Creature.h"
#include "Game/Compass.h"
#include "Raylib/terminal.h"

#define VIEW_INPUT_COOLDOWN 2
#define VIEW_BLINK_COOLDOWN 10

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
	static int inputTimer = 0;

	if (IsKeyPressed(KEY_ESCAPE))
		PushView(&VIEW_GAME_PAUSED);

	// TEMP: Ideally keys have a hold-delay-process behaviour. This 
	// temporary hack makes it easier to see each step without implementing
	// that just yet
	if (inputTimer > 0) {
		inputTimer--;
		return;
	}

	if (IsKeyDown(KEY_UP)) {
		CreatureWalkOrInteract(GetCreatureProtagonist(), COMPASS_NORTH);
		inputTimer = VIEW_INPUT_COOLDOWN;
	} else if (IsKeyDown(KEY_RIGHT)) {
		CreatureWalkOrInteract(GetCreatureProtagonist(), COMPASS_EAST);
		inputTimer = VIEW_INPUT_COOLDOWN;
	} else if (IsKeyDown(KEY_DOWN)) {
		CreatureWalkOrInteract(GetCreatureProtagonist(), COMPASS_SOUTH);
		inputTimer = VIEW_INPUT_COOLDOWN;
	} else if (IsKeyDown(KEY_LEFT)) {
		CreatureWalkOrInteract(GetCreatureProtagonist(), COMPASS_WEST);
		inputTimer = VIEW_INPUT_COOLDOWN;
	}
}

static void OnRenderView(void)
{
	// TODO: HUD
}
