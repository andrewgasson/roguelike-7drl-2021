#include "Game/Prompt.h"

#include "Game/View.h"
#include "Raylib/raylib.h"
#include "Raylib/terminal.h"
#include "Raylib/terminaldraw.h"
#include "Raylib/terminalwrite.h"
#include <string.h>

typedef enum {
	VIEW_SELECTION_UNSELECTED,
	VIEW_SELECTION_ACCEPT,
	VIEW_SELECTION_DECLINE
} ViewSelection;

static void OnOpenView(void);
static void OnCloseView(void);
static void OnControlView(void);
static void OnRenderView(void);

static const View BOOL_PROMPT_VIEW = {
	.Open = OnOpenView,
	.Close = OnCloseView,
	.Control = OnControlView,
	.Render = OnRenderView,
	.requireGameWorldRender = false
};

static bool promptIsOpen;
static BoolPromptCallback promptOnAccept;
static BoolPromptCallback promptOnDecline;
static const char *promptTitleText;
static const char *promptMessageText;
static const char *promptAcceptText;
static const char *promptDeclineText;
static ViewSelection promptSelection;

void OpenBoolPrompt(BoolPromptCallback onAccept, BoolPromptCallback onDecline, const char *titleText, const char *messageText, const char *acceptText, const char *declineText)
{
	// CRASH: Only one prompt allowed at a time.
	if (promptIsOpen) {
		TraceLog(LOG_ERROR, "PROMPT: Only one BoolPrompt allowed open at a time");
		return;
	}

	promptIsOpen = true;
	promptOnAccept = onAccept;
	promptOnDecline = onDecline;
	promptTitleText = titleText;
	promptMessageText = messageText;
	promptAcceptText = acceptText;
	promptDeclineText = declineText;

	PushView(&BOOL_PROMPT_VIEW);
}

static void OnOpenView(void)
{
	promptSelection = VIEW_SELECTION_UNSELECTED;
}

static void OnCloseView(void)
{
	// Do nothing
}

static void OnControlView(void)
{
	// TODO
}

static void OnRenderView(void)
{
	// Box
	int boxPosX;
	int boxPosY;
	int boxWidth;
	int boxHeight;
	TerminalTile boxFill;
	TerminalTile boxOutline;

	// Layout box
	boxWidth = 40;
	boxHeight = 20;
	boxPosX = (GetTerminalWidth() - boxWidth) / 2;
	boxPosY = (GetTerminalHeight() - boxHeight) / 2;
	boxFill = (TerminalTile) { .background = WHITE, .foreground = BLACK, .symbol = 'X' };
	boxOutline = (TerminalTile) { .background = BLACK, .foreground = DARKGRAY, .symbol = '+' };
	DrawTerminalBox(boxPosX, boxPosY, boxWidth, boxHeight, boxFill, boxOutline);

	// Layout title text
	if (promptTitleText) {
		int titlePosX;
		int titleLength;

		SetTerminalWriteBackPaint(boxFill.background);
		SetTerminalWriteForePaint(boxOutline.foreground);
		titleLength = strlen(promptTitleText);

		if (titleLength > boxWidth - 2)
			titleLength = boxWidth - 2;

		titlePosX = (boxWidth - titleLength) / 2;
		SetTerminalCursorWrap(false, false);
		SetTerminalCursorXY(titlePosX, boxPosY);
		WriteTerminalText(promptTitleText);
		MoveTerminalCursorNextLine();
	}

	// Layout message text
	if (promptMessageText) {
		const int messageHorizontalPadding = 4;
		const int messageVerticalPadding = 8;
		int messageLineStart;
		int messageLength;
		int messageWidth;
		int messageHeight;
		
		messageLineStart = 0;
		messageLength = strlen(promptMessageText);
		messageWidth = boxWidth - messageHorizontalPadding;
		messageHeight = boxHeight - messageVerticalPadding;
		SetTerminalCursorWrap(true, true);
		SetTerminalWriteBackPaint(ALPHA_BLACK);
		SetTerminalWriteForePaint(RAYWHITE);

		while (messageLength > 0) {
			MoveTerminalCursorRight(messageHorizontalPadding / 2);
			WriteTerminalTextLength(&promptMessageText[messageLineStart], messageWidth);
			messageLineStart += messageWidth;
			messageLength -= messageWidth;
			MoveTerminalCursorNextLine();
		}
	}

	// Layout buttons
	// TODO: Finish implementation!
	if (promptAcceptText && promptDeclineText) {
		//
	} else if (promptAcceptText) {
		//
	} else {
		//
	}
}
