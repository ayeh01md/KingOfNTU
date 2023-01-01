#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Map.h"

GameObject* player;
/*
SDL_Texture* playerTex;
SDL_Rect srcR, destR;
*/
SDL_Renderer* Game::renderer = nullptr;
Map* map;

Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int width, int height, bool fullscreen)
{
	int flags = 0;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}


	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystem Initialised!" << std::endl;
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);

		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer,255,255,255,255);
		}
		isRunning = true;
	}
	/*
	SDL_Surface* tmpSurface = IMG_Load("img/yeh.png");
	playerTex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	*/

	//Add more according to what objects are added
	player = new GameObject("img/yeh.png", 0, 0);
	map = new Map();
}


void Game::handleEvents()
{
	SDL_Event event;

	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update()
{
	cnt++;
	/*
	destR.h = 64;
	destR.w = 64;
	destR.x = cnt;
	*/

	//Add more according to what objects need to be updated
	player->Update();
	//map->LoadMap();
	std::cout << cnt << std::endl;
}

void Game::render()
{
	SDL_RenderClear(renderer);
	//SDL_RenderCopy(renderer, playerTex, NULL, &destR);
	// 
	//Add more according to what objects need to be rendered
	player->Render();
	map->DrawMap();
	SDL_RenderPresent(renderer);
}
void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	//std::cout << "Game Cleaned" << std::endl;

}