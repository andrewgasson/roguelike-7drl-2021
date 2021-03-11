#include "Game/Prompt.h"

#include "Game/Input.h"
#include "Game/View.h"
#include "Raylib/raylib.h"
#include "Raylib/terminal.h"
#include "Raylib/terminaldraw.h"
#include "Raylib/terminalgui.h"
#include "Raylib/terminalwrite.h"
#include <string.h>

typedef enum {
	BOOL_PROMPT_CURSOR_UNSELECTED,
	BOOL_PROMPT_CURSOR_ACCEPT,
	BOOL_PROMPT_CURSOR_DECLINE
} BoolPromptCursor;

#define BOOL_PROMPT_DEFAULT_ACCEPT "Accept"
#define BOOL_PROMPT_DEFAULT_DECLINE "Decline"

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
static BoolPromptCursor promptSelection;

void OpenBoolPrompt(BoolPromptCallback onAccept, BoolPromptCallback onDecline, const char *titleText, const char *messageText, const char *acceptText, const char *declineText)
{
	// CRASH: Only one prompt allowed at a time
	if (promptIsOpen) {
		TraceLog(LOG_ERROR, "PROMPT: BoolPrompt is already open");
		return;
	}

	promptIsOpen = true;
	promptOnAccept = onAccept;
	promptOnDecline = onDecline;
	promptTitleText = titleText;
	promptMessageText = messageText;
	promptAcceptText = (acceptText) ? acceptText : BOOL_PROMPT_DEFAULT_ACCEPT;
	promptDeclineText = (declineText) ? declineText : BOOL_PROMPT_DEFAULT_DECLINE;

	PushView(&BOOL_PROMPT_VIEW);
}

static void OnOpenView(void)
{
	promptSelection = BOOL_PROMPT_CURSOR_UNSELECTED;
}

static void OnCloseView(void)
{
	promptIsOpen = false;
}

static void OnControlView(void)
{
	if (IsInputActive(INPUT_UI_CANCEL)) {
		PopView();

		if (promptOnDecline)
			promptOnDecline();
	} else if (IsInputActive(INPUT_UI_SUBMIT)) {
		if (promptSelection == BOOL_PROMPT_CURSOR_ACCEPT) {
			PopView();

			if (promptOnAccept)
				promptOnAccept();
		} else if (promptSelection == BOOL_PROMPT_CURSOR_DECLINE) {
			PopView();

			if (promptOnDecline)
				promptOnDecline();
		}
	} else if (IsInputActive(INPUT_UI_LEFT)) {
		if (promptAcceptText)
			promptSelection = BOOL_PROMPT_CURSOR_ACCEPT;
	} else if (IsInputActive(INPUT_UI_RIGHT)) {
		if (promptDeclineText)
			promptSelection = BOOL_PROMPT_CURSOR_DECLINE;
	} else if (IsInputActive(INPUT_UI_UP)) {
		promptSelection = BOOL_PROMPT_CURSOR_UNSELECTED;
	}
}

static void OnRenderView(void)
{
	static const int panelWidth = 40;
	static const TerminalTile panelFill = { .background = DARKGRAY, .foreground = WHITE, .symbol = ' ' };
	static const TerminalTile panelOutline = { .background = DARKGRAY, .foreground = WHITE, .symbol = ' ' };
	int messageLength;
	int messageWidth;
	int messageHeight;
	int panelPosX;
	int panelPosY;
	int panelHeight;

	// Fade entire background
	// Box fill does not support transparency, so this doesn't behave as expected
//	DrawTerminalBoxFill(0, 0, GetTerminalWidth(), GetTerminalHeight(), PROMPT_TILE);

	// Calculate message info
	messageLength = promptMessageText ? strlen(promptMessageText) : 0;
	messageWidth = panelWidth - 4;
	messageHeight = (messageLength > 0) ? messageLength / messageWidth : 0;

	// Layout panel
	panelHeight = 4 + messageHeight + (promptAcceptText != NULL || promptDeclineText != NULL);
	panelPosX = GetTerminalWidth() - panelWidth;
	panelPosX = (panelPosX > 0) ? panelPosX / 2 : 0;
	panelPosY = GetTerminalHeight() - panelHeight;
	panelPosY = (panelPosY > 0) ? panelPosY / 2 : 0;
	DrawTerminalBox(panelPosX, panelPosY, panelWidth, panelHeight, panelFill, panelOutline);

	// Layout title
	if (promptTitleText) {
		int titlePosX;
		int titleLength;

		titleLength = strlen(promptTitleText);
		titleLength = (titleLength > panelWidth) ? panelWidth : titleLength;
		titlePosX = panelPosX + ((panelWidth - titleLength) / 2);
		SetTerminalCursorWrap(false, false);
		SetTerminalWriteBackPaint(panelOutline.background);
		SetTerminalWriteForePaint(panelOutline.foreground);
		SetTerminalCursorXY(titlePosX, panelPosY);
		WriteTerminalTextLength(promptTitleText, titleLength);
	}

	// Layout message
	if (messageLength > 0) {
		int messageLineStart;
		int messageLengthRemainder;

		messageLineStart = 0;
		messageLengthRemainder = messageLength;
		SetTerminalCursorWrap(true, true);
		MoveTerminalCursorDown(2);
		SetTerminalWriteBackPaint(panelFill.background);
		SetTerminalWriteForePaint(panelFill.foreground);

		while (messageLengthRemainder > 0) {
			int messageLineEnd;

			messageLineEnd = (messageWidth < messageLengthRemainder) ? messageWidth : messageLengthRemainder;
			SetTerminalCursorXY(panelPosX + 2, GetTerminalCursorY());
			WriteTerminalTextLength(&promptMessageText[messageLineStart], messageLineEnd);
			messageLineStart += messageLineEnd;
			messageLengthRemainder -= messageLineEnd;
			MoveTerminalCursorNextLine();
		}
	}

	// Layout options
	{
		int acceptLength;
		int declineLength;
		int acceptStart;
		int declineStart;
		int totalLength;
		Color acceptForeground;
		Color acceptBackground;
		Color declineForeground;
		Color declineBackground;

		acceptLength = strlen(promptAcceptText);
		declineLength = strlen(promptDeclineText);
		totalLength = (acceptLength + 2) + 2 + (declineLength + 2);
		acceptStart = panelPosX + ((panelWidth - totalLength) / 2);
		declineStart = (acceptStart + acceptLength) + 3;
		acceptForeground = (promptSelection == BOOL_PROMPT_CURSOR_ACCEPT) ? panelFill.background : panelFill.foreground;
		acceptBackground = (promptSelection == BOOL_PROMPT_CURSOR_ACCEPT) ? panelFill.foreground : panelFill.background;
		declineForeground = (promptSelection == BOOL_PROMPT_CURSOR_DECLINE) ? panelFill.background : panelFill.foreground;
		declineBackground = (promptSelection == BOOL_PROMPT_CURSOR_DECLINE) ? panelFill.foreground : panelFill.background;
		MoveTerminalCursorDown(1);
		DrawTerminalGuiButton(acceptStart, GetTerminalCursorY(), promptAcceptText, acceptLength, acceptBackground, acceptForeground);
		DrawTerminalGuiButton(declineStart, GetTerminalCursorY(), promptDeclineText, declineLength, declineBackground, declineForeground);
	}
}
