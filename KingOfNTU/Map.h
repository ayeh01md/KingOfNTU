#pragma once

#include "Game.h"

class Map
{
public:
	Map();
	~Map();

	void LoadMap(int arr[9][16]);
	void DrawMap();

private:
	SDL_Rect src, dest;

	SDL_Texture* floor;

	int map[9][16];
};
