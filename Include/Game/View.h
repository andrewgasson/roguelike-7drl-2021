#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include "Raylib/raylib.h"

typedef struct View {
	void (*Open)(void);
	void (*Close)(void);
	void (*Control)(void);
	void (*Render)(void);
	bool requireGameWorldRender;
} View;

const View *PeekView(void);
void PushView(const View *view);
void PopView(void);
void PopAllViews(void);
void SetView(const View *view);
bool IsViewOpen(const View *view);
int CountViews(void);
int MaxViews(void);
bool ShouldRenderGameWorld(void);
void ControlView(void);
void RenderViews(void);

extern const View VIEW_DEV_SANDBOX;
extern const View VIEW_GAME_DEFAULT;
extern const View VIEW_GAME_PAUSED;
extern const View VIEW_MAIN_MENU;

#endif // GAME_VIEW_H
