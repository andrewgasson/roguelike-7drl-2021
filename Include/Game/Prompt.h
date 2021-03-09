#ifndef GAME_PROMPT_H
#define GAME_PROMPT_H

typedef void (*BoolPromptCallback)(void);

void OpenBoolPrompt(BoolPromptCallback onAccept, BoolPromptCallback onDecline, const char *titleText, const char *messageText, const char *acceptText, const char *declineText);
void OpenMessagePrompt(const char *titleText, const char *messageText, const char *acceptText);
void OpenStringPrompt(char **outString, int maxStringLength, const char *titleText, const char *messageText, const char *acceptText);

#endif // GAME_PROMPT_H
