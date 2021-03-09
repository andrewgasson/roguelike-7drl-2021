#include "Game/View.h"

#include "Game/View.h"

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
	// TODO
}

static void OnOpenView(void)
{
	//
}

static void OnCloseView(void)
{
	//
}

static void OnControlView(void)
{
	//
}

static void OnRenderView(void)
{
	//
}
