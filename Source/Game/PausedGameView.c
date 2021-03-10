#include "Game/View.h"

#include "Game/Compass.h"
#include "Game/Creature.h"
#include "Game/Prompt.h"
#include "Raylib/terminal.h"
#include "Raylib/terminaldraw.h"
#include "Raylib/terminalwrite.h"

typedef enum {
	VIEW_CURSOR_CONTINUE,
	VIEW_CURSOR_NEW_GAME,
	VIEW_CURSOR_LOAD_GAME,
	VIEW_CURSOR_SAVE_GAME,
	VIEW_CURSOR_HELP,
	VIEW_CURSOR_QUIT
} ViewCursor;

static void OnOpenView(void);
static void OnCloseView(void);
static void OnControlView(void);
static void OnRenderView(void);

const View VIEW_GAME_PAUSED = {
	.Open = OnOpenView,
	.Close = OnCloseView,
	.Control = OnControlView,
	.Render = OnRenderView,
	.requireGameWorldRender = true
};

static ViewCursor viewCursor;

static void OnOpenView(void)
{
	viewCursor = VIEW_CURSOR_CONTINUE;
}

static void OnCloseView(void)
{
	// Do nothing
}

static void OnControlView(void)
{
	if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_TAB)) {
		PopView();
	} else if (IsKeyPressed(KEY_UP) && viewCursor > VIEW_CURSOR_CONTINUE) {
		viewCursor--;
	} else if (IsKeyPressed(KEY_DOWN) && viewCursor < VIEW_CURSOR_QUIT) {
		viewCursor++;
	} else if (IsKeyPressed(KEY_ENTER)) {
		if (viewCursor == VIEW_CURSOR_CONTINUE)
			PopView();
		else if (viewCursor == VIEW_CURSOR_NEW_GAME)
			OpenNewGamePrompt();
		else if (viewCursor == VIEW_CURSOR_QUIT)
			OpenQuitGamePrompt();
	}
}

static void OnRenderView(void)
{
	static const int panelPosX = 3;
	static const int panelWidth = 22;
	static const TerminalTile panelTile = { .background = BLACK, .foreground = WHITE, .symbol = ' ' };
	static const char * const title = "[ Paused ]";
	static const int titleLength = 10;
	static const Color selectedColor = WHITE;
	static const Color unselectedColor = GRAY;
	static const int leftPadding = (panelWidth - titleLength) / 2;

	// Layout panel
	DrawTerminalBoxFill(panelPosX, 0, panelWidth, GetScreenHeight(), panelTile);

	// Layout title
	SetTerminalCursorWrap(false, false);
	SetTerminalWriteBackPaint(ALPHA_BLACK);
	SetTerminalWriteForePaint(WHITE);
	SetTerminalCursorXY(leftPadding, 3);
	WriteTerminalText(title);

	// Layout continue option
	SetTerminalCursorXY(leftPadding, GetTerminalCursorY() + 3);

	if (viewCursor == VIEW_CURSOR_CONTINUE) {
		SetTerminalWriteForePaint(WHITE);
		WriteTerminalText("> Continue");
	} else {
		SetTerminalWriteForePaint(GRAY);
		WriteTerminalText("  Continue");
	}

	// Layout new game option
	SetTerminalCursorXY(leftPadding, GetTerminalCursorY() + 2);

	if (viewCursor == VIEW_CURSOR_NEW_GAME) {
		SetTerminalWriteForePaint(WHITE);
		WriteTerminalText("> New Game");
	} else {
		SetTerminalWriteForePaint(GRAY);
		WriteTerminalText("  New Game");
	}

	// Layout load game option
	SetTerminalCursorXY(leftPadding, GetTerminalCursorY() + 2);

	if (viewCursor == VIEW_CURSOR_LOAD_GAME) {
		SetTerminalWriteForePaint(WHITE);
		WriteTerminalText("> Load Game");
	} else {
		SetTerminalWriteForePaint(GRAY);
		WriteTerminalText("  Load Game");
	}

	// Layout save game option
	SetTerminalCursorXY(leftPadding, GetTerminalCursorY() + 2);

	if (viewCursor == VIEW_CURSOR_SAVE_GAME) {
		SetTerminalWriteForePaint(WHITE);
		WriteTerminalText("> Save Game");
	} else {
		SetTerminalWriteForePaint(GRAY);
		WriteTerminalText("  Save Game");
	}

	// Layout help option
	SetTerminalCursorXY(leftPadding, GetTerminalCursorY() + 2);

	if (viewCursor == VIEW_CURSOR_HELP) {
		SetTerminalWriteForePaint(WHITE);
		WriteTerminalText("> Help");
	} else {
		SetTerminalWriteForePaint(GRAY);
		WriteTerminalText("  Help");
	}

	// Layout quit option
	SetTerminalCursorXY(leftPadding, GetTerminalCursorY() + 2);

	if (viewCursor == VIEW_CURSOR_QUIT) {
		SetTerminalWriteForePaint(WHITE);
		WriteTerminalText("> Quit");
	} else {
		SetTerminalWriteForePaint(GRAY);
		WriteTerminalText("  Quit");
	}
}
