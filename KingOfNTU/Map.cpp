#include "Map.h"
#include "TextureManager.h"

int lvl1[9][16] =
{
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	
};

Map::Map()
{
	floor = TextureManager::LoadTexture("img/square.png");

	LoadMap(lvl1);
	src.x = 0;
	src.y = 0;
	src.w = dest.w = 80;//Displayed Width
	src.h = dest.h = 80;//Displayed Height

	dest.x = dest.y = 0;
}

Map::~Map()
{
	SDL_DestroyTexture(floor);
}
void Map::LoadMap(int arr[9][16])
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			map[i][j] = arr[i][j];
		}
	}
}

void Map::DrawMap()
{
	int type = 0;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			type = map[i][j];
			dest.x = j * 80; 
			dest.y = i * 80;
			switch (type)
			{
			case 1:
				TextureManager::Draw(floor, src, dest);
				break;
			default:
				break;
			}



		}
	}



}