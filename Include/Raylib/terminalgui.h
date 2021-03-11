#ifndef TERMINAL_GUI_H
#define TERMINAL_GUI_H

#include "Raylib/raylib.h"
#include "Raylib/terminal.h"

#define TERMINAL_GUI_BUTTON_HORIZONTAL_PADDING 2

void DrawTerminalGuiButton(int x, int y, const char *text, int maxTextLength, Color background, Color foreground);
void DrawTerminalGuiFrame(int x, int y, int width, int height, const char *title, TerminalTile fill, TerminalTile outline, TerminalTile titleTile);

#endif // TERMINAL_GUI_H
