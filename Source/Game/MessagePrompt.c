#include "Game/View.h"

#include "Game/Input.h"
#include "Game/View.h"
#include "Raylib/terminal.h"
#include "Raylib/terminaldraw.h"
#include "Raylib/terminalgui.h"
#include "Raylib/terminalwrite.h"
#include <string.h>

#define MESSAGE_PROMPT_DEFAULT_ACCEPT "Accept"

static void OnOpenView(void);
static void OnCloseView(void);
static void OnControlView(void);
static void OnRenderView(void);

static const View MESSAGE_PROMPT_VIEW = {
	.Open = OnOpenView,
	.Close = OnCloseView,
	.Control = OnControlView,
	.Render = OnRenderView,
	.requireGameWorldRender = false
};

static bool promptIsOpen;
static const char *promptTitleText;
static const char *promptMessageText;
static const char *promptAcceptText;

void OpenMessagePrompt(const char *titleText, const char *messageText, const char *acceptText)
{
	// CRASH: Only one prompt allowed at a time
	if (promptIsOpen) {
		TraceLog(LOG_ERROR, "PROMPT: MessagePrompt is already open");
		return;
	}

	promptIsOpen = true;
	promptTitleText = titleText;
	promptMessageText = messageText;
	promptAcceptText = (acceptText) ? acceptText : MESSAGE_PROMPT_DEFAULT_ACCEPT;

	PushView(&MESSAGE_PROMPT_VIEW);
}

static void OnOpenView(void)
{
	// Do nothing
}

static void OnCloseView(void)
{
	promptIsOpen = false;
}

static void OnControlView(void)
{
	if (IsInputActive(INPUT_UI_SUBMIT))
		PopView();
}

// TODO: Support messages that are so long, they have to wrap to another screen,
// which can be interacted with use LEFT/RIGHT, maybe even HOME/END
static void OnRenderView(void)
{
	static const int frameWidth = 60;
	static const int frameHeight = 20;
	static const int maxMessageHeight = frameHeight - 8;
	static const TerminalTile frameFill = { .background = BLACK, .foreground = WHITE, .symbol = ' ' };
	static const TerminalTile frameOutline = { .foreground = DARKGRAY, .symbol = 203 };
	static const TerminalTile frameOutlineTitle = { .background = GRAY, .foreground = BLACK };
	int framePosX;
	int framePosY;

	// Layout frame
	framePosX = (GetTerminalWidth() - frameWidth) / 2;
	framePosY = (GetTerminalHeight() - frameHeight) / 2;
	DrawTerminalGuiFrame(framePosX, framePosY, frameWidth, frameHeight, promptTitleText, frameFill, frameOutline, frameOutlineTitle);

	// Layout message
	if (promptMessageText) {
		int messageWidth;
		int messageLength;
		int messageLineStart;
		int messageLengthRemainder;
		int messagePosX;
		int messagePosY;

		messageWidth = frameWidth - 4;
		messageLength = strlen(promptMessageText);
		messageLineStart = 0;
		messageLengthRemainder = messageLength;
		messagePosX = framePosX + 2;
		messagePosY = framePosY + 2;
		SetTerminalCursorWrap(true, true);
		SetTerminalCursorXY(messagePosX, messagePosY);
		SetTerminalWriteBackPaint(frameFill.background);
		SetTerminalWriteForePaint(frameFill.foreground);

		while (messageLengthRemainder > 0) {
			int messageLineEnd;

			messageLineEnd = (messageWidth < messageLengthRemainder) ? messageWidth : messageLengthRemainder;
			SetTerminalCursorXY(messagePosX, GetTerminalCursorY());
			WriteTerminalTextLength(&promptMessageText[messageLineStart], messageLineEnd);
			messageLineStart += messageLineEnd;
			messageLengthRemainder -= messageLineEnd;
			MoveTerminalCursorNextLine();
		}
	}

	// Layout options
	{
		int acceptLength;
		int acceptPosX;
		int acceptPosY;

		acceptLength = strlen(promptAcceptText);
		acceptPosX = framePosX + ((frameWidth - acceptLength - 2) / 2);
		acceptPosY = framePosY + frameHeight - 3;
		MoveTerminalCursorDown(1);
		DrawTerminalGuiButton(acceptPosX, acceptPosY, promptAcceptText, acceptLength, GRAY, BLACK);
	}
}
