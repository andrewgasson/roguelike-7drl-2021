#include "Game/View.h"

#include "Game/Creature.h"
#include "Game/Compass.h"
#include "Raylib/terminal.h"

#define VIEW_INPUT_COOLDOWN 2
#define VIEW_BLINK_COOLDOWN 10

static void Open(void);
static void Close(void);
static void Control(void);
static void Render(void);

const View VIEW_GAME_DEFAULT = {
	.Open = Open,
	.Close = Close,
	.Control = Control,
	.Render = Render,
	.requireGameWorldRender = true
};

static void Open(void)
{
	//
}

static void Close(void)
{
	//
}

static void Control(void)
{
	static int inputTimer = 0;

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

static void Render(void)
{
	static int blinkTimer = 0;
	TerminalTile gold;

	if (blinkTimer > 0) {
		blinkTimer--;
	} else {
		blinkTimer = VIEW_BLINK_COOLDOWN;

		if (ColorToInt(gold.background) == ColorToInt(BLUE))
			gold.background = RED;
		else
			gold.background = BLUE;
	}

	gold.foreground = GOLD;
	gold.symbol = '$';
	SetTerminalTile(0, 0, gold);
}
