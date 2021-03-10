#ifndef TERMINAL_GUI_H
#define TERMINAL_GUI_H

#include "Raylib/raylib.h"

#define TERMINAL_GUI_BUTTON_HORIZONTAL_PADDING 2

void DrawTerminalGuiButton(int x, int y, const char *text, int maxTextLength, Color background, Color foreground);

#endif // TERMINAL_GUI_H
