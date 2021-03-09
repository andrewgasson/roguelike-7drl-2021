#include "Raylib/terminaldraw.h"

static int ClampInt(int i, int min, int max);
static void SwapIntScalar(int *i0, int *i1);

inline void DrawTerminalBox(int x, int y, int width, int height, TerminalTile fill, TerminalTile outline)
{
	// Efficient because there are no branches, and the outline might still 
	// be culled entirely
	DrawTerminalBoxFill(x, y, width, height, fill);
//	DrawTerminalBoxOutline(x, y, width, height, outline);
}

void DrawTerminalBoxFill(int x, int y, int width, int height, TerminalTile fill)
{
	// BUG: TODO: There are a bunch of wierd bugs with this for some reason.
//	int terminalWidth;
//	int terminalHeight;
//
//	if (width < 0)
//		SwapIntScalar(&x, &width);
//
//	if (height < 0)
//		SwapIntScalar(&y, &height);
//
//	terminalWidth = GetTerminalWidth();
//	terminalHeight = GetTerminalHeight();
	width = x + width;
	height = y + height;
//	x = ClampInt(x, 0, terminalWidth);
//	y = ClampInt(y, 0, terminalHeight);
//	width = ClampInt(width, 0, terminalWidth);
//	height = ClampInt(height, 0, terminalHeight);

	for (; y < height; y++) {
		for (; x < width; x++)
			SetTerminalTile(x, y, fill);
	}
}

void DrawTerminalBoxOutline(int x, int y, int width, int height, TerminalTile outline)
{
	// TODO: Implement outline that doesn't go out of bounds.
	/*
	int terminalWidth;
	int terminalHeight;
	int edgePosX;
	int edgePosY;
	int edgePosWidth;
	int edgePosHeight;

	// TODO!!!

	terminalWidth = GetTerminalWidth();
	terminalHeight = GetTerminalHeight();
	SortIntScalar(&x, &width);
	SortIntScalar(&y, &height);
	edgePosX = x;
	edgePosY = y;
	edgePosWidth = width;
	edgePosHeight = height;

	// Draw top-horizontal
	// Draw vertical sides
	// Draw bottom-horizontal
	*/
}

inline static int ClampInt(int i, int min, int max)
{
	return (i < min) ? min : (i > max) ? max : i;
}

inline static void SwapIntScalar(int *i0, int *i1)
{
	int store;

	store = *i0;
	*i0 = *i1;
	*i1 = store;
}
