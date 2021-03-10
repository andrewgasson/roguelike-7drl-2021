#include "Raylib/terminalgui.h"

#include "Raylib/terminaldraw.h"
#include "Raylib/terminalwrite.h"
#include <string.h>

void DrawTerminalGuiButton(int x, int y, const char *text, int maxTextLength, Color background, Color foreground)
{
	Color prevBackPaint;
	Color prevForePaint;
	int prevCursorX;
	int prevCursorY;
	int textLength;
	int width;

	// Store previous settings
	prevBackPaint = GetTerminalWriteBackPaint();
	prevForePaint = GetTerminalWriteForePaint();
	prevCursorX = GetTerminalCursorX();
	prevCursorY = GetTerminalCursorY();

	// Calculate info
	textLength = (text) ? strlen(text) : 0;
	textLength = (textLength > maxTextLength) ? maxTextLength : textLength;
	width = x + textLength + TERMINAL_GUI_BUTTON_HORIZONTAL_PADDING;

	// Draw
	SetTerminalWriteBackPaint(background);
	SetTerminalWriteForePaint(foreground);
	SetTerminalCursorXY(x, y);
	WriteTerminalLetter(' ');

	if (textLength > 0)
		WriteTerminalTextLength(text, textLength);

	WriteTerminalLetter(' ');

	// Reset settings
	SetTerminalWriteBackPaint(prevBackPaint);
	SetTerminalWriteForePaint(prevForePaint);
	SetTerminalCursorXY(prevCursorX, prevCursorY);
}
