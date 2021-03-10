#ifndef GAME_PROMPT_H
#define GAME_PROMPT_H

typedef void (*BoolPromptCallback)(void);

#include "Raylib/raylib.h"
#include "Raylib/terminal.h"

#define PROMPT_COLOR CLITERAL(Color){ 0, 0, 0, 128 }
#define PROMPT_TILE CLITERAL(TerminalTile) { .background = PROMPT_COLOR, .foreground = PROMPT_COLOR, .symbol = ' ' }

void OpenBoolPrompt(BoolPromptCallback onAccept, BoolPromptCallback onDecline, const char *titleText, const char *messageText, const char *acceptText, const char *declineText);
void OpenMessagePrompt(const char *titleText, const char *messageText, const char *acceptText);
void OpenStringPrompt(char **outString, int maxStringLength, const char *titleText, const char *messageText, const char *acceptText);

void OpenQuitPrompt(void);

#endif // GAME_PROMPT_H
