#include "Game/View.h"

#include "Game/Game.h"
#include "Game/Input.h"
#include "Game/Main.h"
#include "Game/Prompt.h"
#include "Raylib/terminal.h"
#include "Raylib/terminalwrite.h"
#include <stdlib.h> // for NULL

typedef enum {
	MAIN_MENU_CURSOR_NEW_GAME,
	MAIN_MENU_CURSOR_LOAD_GAME,
	MAIN_MENU_CURSOR_HELP,
	MAIN_MENU_CURSOR_QUIT
} MainMenuCursor;

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

static MainMenuCursor mainMenuCursor;

static void OnOpenView(void)
{
	mainMenuCursor = MAIN_MENU_CURSOR_NEW_GAME;
}

static void OnCloseView(void)
{
	// Do nothing
}

static void OnControlView(void)
{
	if (IsInputActive(INPUT_UI_CANCEL)) {
		OpenQuitPrompt();
	} else if (IsInputActive(INPUT_UI_UP)) {
		if (mainMenuCursor > MAIN_MENU_CURSOR_NEW_GAME)
			mainMenuCursor--;
	} else if (IsInputActive(INPUT_UI_DOWN)) {
		if (mainMenuCursor < MAIN_MENU_CURSOR_QUIT)
			mainMenuCursor++;
	} else if (IsInputActive(INPUT_UI_SUBMIT)) {
		switch (mainMenuCursor) {
		case MAIN_MENU_CURSOR_NEW_GAME:
			NewGame();
			SetView(&VIEW_GAME_DEFAULT);
			break;
		case MAIN_MENU_CURSOR_LOAD_GAME:
			TraceLog(LOG_INFO, "VIEW: MainMenu: Loading new game");
			break;
		case MAIN_MENU_CURSOR_HELP:
			OpenMessagePrompt("Help", "Press button. Bump red \"w\" 'til gone.", "Thanks!");
			break;
		case MAIN_MENU_CURSOR_QUIT:
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

	if (mainMenuCursor == MAIN_MENU_CURSOR_NEW_GAME) {
		SetTerminalWriteForePaint(WHITE);
		WriteTerminalText("  > New Game");
	} else {
		SetTerminalWriteForePaint(GRAY);
		WriteTerminalText("    New Game");
	}

	// Draw "Load Game" option
	MoveTerminalCursorNextLine();

	if (mainMenuCursor == MAIN_MENU_CURSOR_LOAD_GAME) {
		SetTerminalWriteForePaint(WHITE);
		WriteTerminalText("  > Load Game");
	} else {
		SetTerminalWriteForePaint(GRAY);
		WriteTerminalText("    Load Game");
	}

	// Draw "Help" option
	MoveTerminalCursorNextLine();

	if (mainMenuCursor == MAIN_MENU_CURSOR_HELP) {
		SetTerminalWriteForePaint(WHITE);
		WriteTerminalText("  > Help");
	} else {
		SetTerminalWriteForePaint(GRAY);
		WriteTerminalText("    Help");
	}

	// Draw "Quit" option
	MoveTerminalCursorNextLine();

	if (mainMenuCursor == MAIN_MENU_CURSOR_QUIT) {
		SetTerminalWriteForePaint(WHITE);
		WriteTerminalText("  > Quit");
	} else {
		SetTerminalWriteForePaint(GRAY);
		WriteTerminalText("    Quit");
	}
}
