#ifndef GAME_COMPASS_H
#define GAME_COMPASS_H

typedef enum Compass {
	COMPASS_NORTH,
	COMPASS_EAST,
	COMPASS_SOUTH,
	COMPASS_WEST
} Compass;

#include "Raylib/raylib.h"

Vector2 CompassToVector2(Compass compass);

#endif // GAME_COMPASS_H
