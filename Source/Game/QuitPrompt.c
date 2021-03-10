#include "Game/Prompt.h"

#include "Game/Main.h"
#include <stdlib.h> // for NULL

void OpenQuitPrompt(void)
{
	OpenBoolPrompt(QuitApplication, NULL, "Exit to Desktop", "Are you sure you want to quit?", "Yes", "No");
}
