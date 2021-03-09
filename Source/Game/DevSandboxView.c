#include "Game/View.h"

#include "Game/Main.h"
#include "Game/Prompt.h"
#include "Raylib/terminal.h"
#include "Raylib/terminaldraw.h"
#include "Raylib/terminalwrite.h"
#include <stdlib.h> // for NULL

static void OnOpenView(void);
static void OnCloseView(void);
static void OnControlView(void);
static void OnRenderView(void);

const View VIEW_DEV_SANDBOX = {
	.Open = OnOpenView,
	.Close = OnCloseView,
	.Control = OnControlView,
	.Render = OnRenderView,
	.requireGameWorldRender = false
};

static void OnOpenView(void)
{
	// Do nothing
}

static void OnCloseView(void)
{
	// Do nothing
}

static void OnControlView(void)
{
	// Do nothing
}

static void OnRenderView(void)
{
	// Do nothing
}
