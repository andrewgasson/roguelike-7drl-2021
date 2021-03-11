#include "Raylib/terminalgui.h"

#include "Raylib/terminaldraw.h"
#include "Raylib/terminalwrite.h"
#include <string.h>

typedef struct TerminalWriteSettings {
	Color backPaint;
	Color forePaint;
	bool wrapHorizontal;
	bool wrapVertical;
	int cursorX;
	int cursorY;
} TerminalWriteSettings;

static TerminalWriteSettings StoreTerminalWriteSettings(void)
{
	TerminalWriteSettings result;

	result.backPaint = GetTerminalWriteBackPaint();
	result.forePaint = GetTerminalWriteForePaint();
	result.wrapHorizontal = GetTerminalCursorWrapHorizontal();
	result.wrapVertical = GetTerminalCursorWrapVertical();
	result.cursorX = GetTerminalCursorX();
	result.cursorY = GetTerminalCursorY();

	return result;
}

static void RestoreTerminalWriteSettings(TerminalWriteSettings settings)
{
	SetTerminalWriteBackPaint(settings.backPaint);
	SetTerminalWriteForePaint(settings.forePaint);
	SetTerminalCursorWrap(settings.wrapHorizontal, settings.wrapVertical);
	SetTerminalCursorXY(settings.cursorX, settings.cursorY);
}

void DrawTerminalGuiButton(int x, int y, const char *text, int maxTextLength, Color background, Color foreground)
{
	TerminalWriteSettings previousSettings;
	Color prevBackPaint;
	Color prevForePaint;
	int prevCursorX;
	int prevCursorY;
	int textLength;
	int width;

	// Store terminal settings
	previousSettings = StoreTerminalWriteSettings();

	// Calculate info
	textLength = (text) ? strlen(text) : 0;
	textLength = (textLength > maxTextLength) ? maxTextLength : textLength;
	width = x + textLength + TERMINAL_GUI_BUTTON_HORIZONTAL_PADDING;

	// Write
	SetTerminalWriteBackPaint(background);
	SetTerminalWriteForePaint(foreground);
	SetTerminalCursorXY(x, y);
	WriteTerminalLetter(' ');

	if (textLength > 0)
		WriteTerminalTextLength(text, textLength);

	WriteTerminalLetter(' ');

	// Restore terminal settings
	RestoreTerminalWriteSettings(previousSettings);
}

void DrawTerminalGuiFrame(int x, int y, int width, int height, const char *titleText, TerminalTile fillTile, TerminalTile outlineTile, TerminalTile titleTile)
{
	DrawTerminalBox(x, y, width, height, fillTile, outlineTile);

	if (titleText) {
		TerminalWriteSettings previousSettings;
		int maxTitleLength;
		int titleLength;
		int titlePosX;

		// Store terminal settings
		previousSettings = StoreTerminalWriteSettings();

		// Calculate info
		maxTitleLength = width - 4;
		titleLength = strnlen(titleText, maxTitleLength);
		titlePosX = x + ((width - titleLength) / 2);

		// Write
		SetTerminalCursorWrap(false, false);
		SetTerminalWriteBackPaint(titleTile.background);
		SetTerminalWriteForePaint(titleTile.foreground);
		SetTerminalCursorXY(titlePosX - 1, y);
		WriteTerminalLetter(' ');
		WriteTerminalText(titleText);
		WriteTerminalLetter(' ');

		// Restore terminal settings
		RestoreTerminalWriteSettings(previousSettings);
	}
}
