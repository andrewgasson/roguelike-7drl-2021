#ifndef GAME_HANDLE_H
#define GAME_HANDLE_H

#include "Raylib/raylib.h"

typedef struct Handle {
	unsigned int version;
	int index;
} Handle;

inline static bool AreHandlesEqual(Handle h0, Handle h1)
{
	return h0.version == h1.version && h0.index == h1.index;
}

#endif // GAME_HANDLE_H
