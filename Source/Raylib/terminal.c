#include "Raylib/terminal.h"

#include <stdlib.h> // for NULL

static int terminalWidth;
static int terminalHeight;
static TerminalTile *terminalBuffer;
static int terminalFontScale;
static Texture2D terminalFont;

void InitTerminal(int width, int height)
{
	if (terminalWidth != 0 && terminalHeight != 0) {
		TraceLog(LOG_ERROR, "TERMINAL: Already initialized");
		return;
	}

	CloseTerminal();
	SetTerminalSize(width, height);
}

void CloseTerminal(void)
{
	if (terminalBuffer) {
		MemFree(terminalBuffer);
		terminalBuffer = NULL;
	}

	terminalWidth = 0;
	terminalHeight = 0;
}

void LoadTerminalFont(const char *fileName, int scale)
{
	Image image;
	Color *colors;

	image = LoadImage(fileName);
	ImageFormat(&image, UNCOMPRESSED_R8G8B8A8);

	// Set scale
	if (scale > 1)
		ImageResizeNN(&image, image.width * scale, image.height * scale);

	terminalFontScale = scale;
	
	// Set transparency based on first pixel
	colors = LoadImageColors(image);
	ImageColorReplace(&image, colors[0], ColorAlpha(colors[0], 0));

	// Load final texture
	UnloadTexture(terminalFont);
	terminalFont = LoadTextureFromImage(image);

	// Cleanup allocations
	UnloadImageColors(colors);
	UnloadImage(image);
}

void ClearTerminal(void)
{
	int i;
	int length;

	length = terminalWidth * terminalHeight;

	for (i = 0; i < length; i++) {
		terminalBuffer[i].background = BLACK;
		terminalBuffer[i].foreground = GRAY;
		terminalBuffer[i].symbol = ' ';
	}
}

int GetTerminalWidth(void)
{
	return terminalWidth;
}

int GetTerminalHeight(void)
{
	return terminalHeight;
}

int GetTerminalFontWidth(void)
{
	return terminalFont.width / 16;
}

int GetTerminalFontHeight(void)
{
	return terminalFont.height / 16;
}

int GetTerminalScreenWidth(void)
{
	return GetTerminalFontWidth() * terminalWidth;
}

int GetTerminalScreenHeight(void)
{
	return GetTerminalFontHeight() * terminalHeight;
}

int GetTerminalFontScale(void)
{
	return terminalFontScale;
}

TerminalTile GetTerminalTile(int x, int y)
{
	return terminalBuffer[(y * terminalHeight) + x];
}

TerminalTile *GetTerminalTileBuffer(void)
{
	return terminalBuffer;
}

bool IsWithinTerminal(int x, int y)
{
	return x >= 0 && x < terminalWidth && y >= 0 && y < terminalHeight;
}

void SetTerminalFontScale(int scale)
{
	if (terminalFontScale == scale) {
		TraceLog(LOG_WARNING, TextFormat("TERMINAL: Terminal font scale is already %d", scale));
		return;
	} else {
		Image image;

		if (scale < 1)
			scale = 1;

		image = GetTextureData(terminalFont);
		UnloadTexture(terminalFont);

		if (terminalFontScale != 1)
			ImageResizeNN(&image, image.width / terminalFontScale, image.height / terminalFontScale);

		ImageResizeNN(&image, image.width * scale, image.height * scale);
		UnloadTexture(terminalFont);
		terminalFont = LoadTextureFromImage(image);
		terminalFontScale = scale;
		UnloadImage(image);
	}
}

void SetTerminalSize(int width, int height)
{
	// EXIT: Already the same size
	if (terminalWidth == width && terminalHeight == height) {
		TraceLog(LOG_WARNING, TextFormat("TERMINAL: Failed to resize terminal to (%dx%d) because terminal is already (%dx%d)", width, height, terminalWidth, terminalHeight));
		return;
	}

	if (terminalBuffer)
		MemFree(terminalBuffer);

	terminalBuffer = MemAlloc(width * height * sizeof(*terminalBuffer));

	// EXIT: Allocation failure
	if (!terminalBuffer) {
		terminalWidth = 0;
		terminalHeight = 0;
		TraceLog(LOG_ERROR, TextFormat("TERMINAL: Allocation failed when setting terminal size to (%dx%d)", width, height));
		return;
	}

	terminalWidth = width;
	terminalHeight = height;
	ClearTerminal();
}

void SetTerminalTile(int x, int y, TerminalTile tile)
{
	terminalBuffer[(y * terminalHeight) + x] = tile;
}

void DrawTerminal(void)
{
	int x;
	int y;
	int xRenderOffset;
	int yRenderOffset;
	int width;
	int height;
	int tileWidth;
	int tileHeight;
	int screenWidth;
	int screenHeight;

	// Store sizes
	width = terminalWidth;
	height = terminalHeight;
	tileWidth = GetTerminalFontWidth();
	tileHeight = GetTerminalFontHeight();
	screenWidth = GetScreenWidth();
	screenHeight = GetScreenHeight();

	// Store render offsets for screen centering
	xRenderOffset = screenWidth - GetTerminalScreenWidth();
	yRenderOffset = screenHeight - GetTerminalScreenHeight();

	if (xRenderOffset < 0)
		xRenderOffset = 0;
	else if (xRenderOffset > 1)
		xRenderOffset /= 2;

	if (yRenderOffset < 0)
		yRenderOffset = 0;
	else if (yRenderOffset > 1)
		yRenderOffset /= 2;

	// Render tiles
	for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++) {
			Vector2 position;
			
			TerminalTile *tile;

			position.x = x * tileWidth;
			position.y = y * tileHeight;
			tile = &terminalBuffer[(y * terminalHeight) + x];

			// Draw background part
			DrawRectangle(
				position.x,
				position.y,
				position.x + tileWidth,
				position.y + tileHeight,
				tile->background);

			// Draw symbol part
			if (tile->symbol != ' ' && tile->symbol != '\n') {
				Rectangle fontCutout;

				fontCutout.x = (tile->symbol / 16) * tileWidth;
				fontCutout.y = (tile->symbol / 16) * tileHeight;
				fontCutout.width = fontCutout.x + tileWidth;
				fontCutout.height = fontCutout.y + tileHeight;

				DrawTextureRec(
					terminalFont,
					fontCutout,
					position,
					tile->foreground);
			}
		}
	}
}
