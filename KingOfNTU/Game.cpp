#include "Game.h"
#include "TextureManager.h"
#include "Map.h"

#include "Components.h"
#include "Vector2D.h"

Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;


auto& newPlayer(manager.addEntity());



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
	map = new Map();

	newPlayer.addComponent<TransformComponent>();
	newPlayer.addComponent<SpriteComponent>("img/yeh.png");
	newPlayer.addComponent<KeyboardController>();
}


void Game::handleEvents()
{


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

	//Add more according to what objects need to be updated
	
	manager.refresh();
	manager.update();
	std::cout << newPlayer.getComponent<TransformComponent>().position.x << "," << newPlayer.getComponent<TransformComponent>().position.y << std::endl;


}

void Game::render()
{
	SDL_RenderClear(renderer);
	//SDL_RenderCopy(renderer, playerTex, NULL, &destR);
	// 
	//Add more according to what objects need to be rendered
	manager.draw();
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