#include "Game/Prompt.h"

#include "Game/Game.h"
#include "Game/View.h"
#include <stdlib.h>

void OpenLevelUpPrompt(int level)
{
	OpenMessagePrompt("Level Up", TextFormat("Congratulations, you are now level %d.", level), "Onward!");
}
