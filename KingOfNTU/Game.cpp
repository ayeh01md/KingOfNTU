#include "Game.h"
#include "TextureManager.h"
#include "Map.h"

#include "Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "AssetManager.h"

Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

AssetManager* Game::assets = new AssetManager(&manager);
bool Game::isRunning = false;

auto& newPlayer(manager.addEntity());
auto& wall(manager.addEntity());



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

	//assets->AddTexture("terrain", "assets/terrain_ss.png");
	assets->AddTexture("player", "img/yeh.png");
	assets->AddTexture("wall", "img/square.png");
	assets->AddTexture("projectile", "img/b_yeh.png");
	newPlayer.addComponent<TransformComponent>();
	newPlayer.addComponent<SpriteComponent>("player", true);
	newPlayer.addComponent<KeyboardController>();
	newPlayer.addComponent<ColliderComponent>("player");
	newPlayer.addGroup(groupPlayers);
	
	//Change ground thickness
	wall.addComponent<TransformComponent>(0.0f, 620.0f, 50, 1280, 1);
	wall.addComponent<SpriteComponent>("wall");
	wall.addComponent<ColliderComponent>("wall");
	wall.addGroup(groupMap);
}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& enemies(manager.getGroup(Game::groupEnemies));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& projectiles(manager.getGroup(Game::groupProjectiles));


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
	Vector2D playerPos = newPlayer.getComponent<TransformComponent>().position;
	SDL_Rect playerCol = newPlayer.getComponent<ColliderComponent>().collider;
	//Add more according to what objects need to be updated
	
	manager.refresh();
	manager.update();

	//assets->CreateProjectile(Vector2D(600, 600), Vector2D(2, 0), 200, 2, "projectile");
	for (auto& c : colliders)
	{
		SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
		if (Collision::CollisionDetect(cCol, playerCol))
		{
			std::cout << "hit" << std::endl;
			newPlayer.getComponent<TransformComponent>().position = playerPos;
		}
	}
	for (auto& p : projectiles)
	{
		if (Collision::CollisionDetect(newPlayer.getComponent<ColliderComponent>().collider, p->getComponent<ColliderComponent>().collider))
		{
			std::cout << "Hit player!" << std::endl;
			p->destroy();
		}
	}
	/*
	for (auto cc : colliders)
	{
		if (Collision::CollisionDetect(newPlayer.getComponent<ColliderComponent>(), *cc))
		{
			//newPlayer.getComponent<TransformComponent>().position = playerPos;
		}
		

	}
	*/
	
	/*
	if (Collision::CollisionDetect(newPlayer.getComponent<ColliderComponent>().collider, wall.getComponent<ColliderComponent>().collider))
	{
		std::cout << "wall hit" << std::endl;
	}
		newPlayer.getComponent<TransformComponent>().position = playerPos;
	*/
	


	//std::cout << newPlayer.getComponent<TransformComponent>().position.x << "," << newPlayer.getComponent<TransformComponent>().position.y << std::endl;


}





void Game::render()
{
	SDL_RenderClear(renderer);
	//SDL_RenderCopy(renderer, playerTex, NULL, &destR);
	// 
	//Add more according to what objects need to be rendered
	//map->DrawMap();

	
	for (auto& t : tiles)
	{
		t->draw();
	}
	
	for (auto& p : players)
	{
		p->draw();
	}
	for (auto& p : projectiles)
	{
		p->draw();
	}

	SDL_RenderPresent(renderer);
}
void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	//std::cout << "Game Cleaned" << std::endl;

}