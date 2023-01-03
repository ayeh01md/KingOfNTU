#pragma once
#include <SDL.h>

class ColliderComponent;

class Collision
{
public:
	static bool CollisionDetect(const SDL_Rect& recA, const SDL_Rect& recB);
	static bool CollisionDetect(const ColliderComponent& colA, const ColliderComponent& colB);
};