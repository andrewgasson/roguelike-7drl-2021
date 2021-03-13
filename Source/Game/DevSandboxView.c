#include "Game/View.h"

#include "Game/Input.h"
#include "Game/Main.h"
#include "Game/Prompt.h"
#include "Raylib/terminal.h"
#include "Raylib/terminaldraw.h"
#include "Raylib/terminalwrite.h"
#include <stdlib.h>
#include <stdint.h>

static void OnOpenView(void);
static void OnCloseView(void);
static void OnControlView(void);
static void OnRenderView(void);

const View VIEW_DEV_SANDBOX = {
	.Open = OnOpenView,
	.Close = OnCloseView,
	.Control = OnControlView,
	.Render = OnRenderView,
	.disableGameActorProcess = true,
	.disableGameWorldRender = true
};

static char sandboxChar = 1;

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
	if (IsInputActive(INPUT_UI_LEFT)) {
		sandboxChar--;
	} else if (IsInputActive(INPUT_UI_RIGHT)) {
		sandboxChar++;
	}
}

static void OnRenderView(void)
{
	SetTerminalWriteForePaint(WHITE);
	SetTerminalCursorXY(0, 0);
	WriteTerminalLetter(sandboxChar);
	MoveTerminalCursorNextLine();
	WriteTerminalText(TextFormat("Dec: %d", sandboxChar));
	MoveTerminalCursorNextLine();
	WriteTerminalText(TextFormat("Hex: %x", sandboxChar & 0xFF));
}
