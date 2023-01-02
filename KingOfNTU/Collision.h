#pragma once
#include <SDL.h>

class Collision
{
public:
	static bool CollisionDetect(const SDL_Rect& recA, const SDL_Rect& recB);
};