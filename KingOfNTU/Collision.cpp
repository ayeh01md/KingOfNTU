#include "Collision.h"
#include <iostream>

bool Collision::CollisionDetect(const SDL_Rect& recA, const SDL_Rect& recB)
{
	if (recA.x + recA.w >= recB.x &&
		recB.x + recB.w >= recA.x &&
		recA.y + recA.h >= recB.y &&
		recB.y + recB.h >= recA.y)
	{
		//std::cout << recA.x + recA.w << ">=" << recB.x;
		return true;
	}

	return false;

}