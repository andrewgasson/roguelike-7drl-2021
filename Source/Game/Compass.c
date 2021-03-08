#include "Game/Compass.h"

Vector2 CompassToVector2(Compass compass)
{
	// Compass is relative to screen (where 0,0 is top,left)
	switch (compass) {
	case COMPASS_NORTH: return (Vector2) {  0, -1 };
	case COMPASS_EAST:  return (Vector2) {  1,  0 };
	case COMPASS_SOUTH: return (Vector2) {  0,  1 };
	case COMPASS_WEST:  return (Vector2) { -1,  0 };
	default:
		TraceLog(LOG_ERROR, TextFormat("COMPASS: CompassToVector2 conversion for \"%d\" not implemented", compass));
		return (Vector2) { 0, 0 };
	}
}
