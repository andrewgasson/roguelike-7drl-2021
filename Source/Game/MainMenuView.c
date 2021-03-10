#include "Game/View.h"

#include "Game/Main.h"
#include "Game/Prompt.h"
#include "Raylib/terminal.h"
#include "Raylib/terminalwrite.h"
#include <stdlib.h> // for NULL

typedef enum {
	VIEW_CURSOR_NEW_GAME,
	VIEW_CURSOR_LOAD_GAME,
	VIEW_CURSOR_HELP,
	VIEW_CURSOR_QUIT
} ViewCursor;

static void OnOpenView(void);
static void OnCloseView(void);
static void OnControlView(void);
static void OnRenderView(void);

const View VIEW_MAIN_MENU = {
	.Open = OnOpenView,
	.Close = OnCloseView,
	.Control = OnControlView,
	.Render = OnRenderView,
	.requireGameWorldRender = false
};

static ViewCursor mainMenuCursor;

static void OnOpenView(void)
{
	mainMenuCursor = VIEW_CURSOR_NEW_GAME;
}

static void OnCloseView(void)
{
	// Do nothing
}

static void OnControlView(void)
{
	if (IsKeyReleased(KEY_ESCAPE)) {
		OpenQuitPrompt();
	} else if (IsKeyPressed(KEY_UP)) {
		if (mainMenuCursor > VIEW_CURSOR_NEW_GAME)
			mainMenuCursor--;
	} else if (IsKeyPressed(KEY_DOWN)) {
		if (mainMenuCursor < VIEW_CURSOR_QUIT)
			mainMenuCursor++;
	} else if (IsKeyPressed(KEY_ENTER)) {
		switch (mainMenuCursor) {
		case VIEW_CURSOR_NEW_GAME:
			TraceLog(LOG_INFO, "VIEW: MainMenu: Starting new game");
			break;
		case VIEW_CURSOR_LOAD_GAME:
			TraceLog(LOG_INFO, "VIEW: MainMenu: Loading new game");
			break;
		case VIEW_CURSOR_HELP:
			TraceLog(LOG_INFO, "VIEW: MainMenu: Showing help menu");
			break;
		case VIEW_CURSOR_QUIT:
			OpenQuitPrompt();
			break;
		default:
			break;
		}
	}
}

static void OnRenderView(void)
{
	// Terminal write setup
	SnapTerminalCursorBegin();
	SetTerminalCursorWrap(true, true);
	SetTerminalWriteBackPaint(BLACK);

	// Draw title
	SetTerminalWriteForePaint(WHITE);
	WriteTerminalText("[Main Menu]");

	// Draw "New Game" option
	MoveTerminalCursorNextLine();

	if (mainMenuCursor == VIEW_CURSOR_NEW_GAME) {
		SetTerminalWriteForePaint(WHITE);
		WriteTerminalText("  > New Game");
	} else {
		SetTerminalWriteForePaint(GRAY);
		WriteTerminalText("    New Game");
	}

	// Draw "Load Game" option
	MoveTerminalCursorNextLine();

	if (mainMenuCursor == VIEW_CURSOR_LOAD_GAME) {
		SetTerminalWriteForePaint(WHITE);
		WriteTerminalText("  > Load Game");
	} else {
		SetTerminalWriteForePaint(GRAY);
		WriteTerminalText("    Load Game");
	}

	// Draw "Help" option
	MoveTerminalCursorNextLine();

	if (mainMenuCursor == VIEW_CURSOR_HELP) {
		SetTerminalWriteForePaint(WHITE);
		WriteTerminalText("  > Help");
	} else {
		SetTerminalWriteForePaint(GRAY);
		WriteTerminalText("    Help");
	}

	// Draw "Quit" option
	MoveTerminalCursorNextLine();

	if (mainMenuCursor == VIEW_CURSOR_QUIT) {
		SetTerminalWriteForePaint(WHITE);
		WriteTerminalText("  > Quit");
	} else {
		SetTerminalWriteForePaint(GRAY);
		WriteTerminalText("    Quit");
	}
}
