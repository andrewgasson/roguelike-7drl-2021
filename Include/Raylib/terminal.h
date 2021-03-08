#ifndef TERMINAL_H
#define TERMINAL_H

#include "raylib.h"

typedef struct TerminalTile {
	Color background;
	Color foreground;
	char symbol;
} TerminalTile;

void InitTerminal(int width, int height);
void CloseTerminal(void);
void LoadTerminalFont(const char *fileName, int scale);
void ClearTerminal(void);
int GetTerminalWidth(void);
int GetTerminalHeight(void);
int GetTerminalFontWidth(void);
int GetTerminalFontHeight(void);
int GetTerminalScreenWidth(void);
int GetTerminalScreenHeight(void);
int GetTerminalFontScale(void);
TerminalTile GetTerminalTile(int x, int y);
TerminalTile *GetTerminalTileBuffer(void);
bool IsWithinTerminal(int x, int y);
void SetTerminalFontScale(int scale);
void SetTerminalSize(int width, int height);
void SetTerminalTile(int x, int y, TerminalTile tile);
void DrawTerminal(void);

#endif // TERMINAL_H
