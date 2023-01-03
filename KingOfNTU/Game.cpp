#include "Game.h"
#include "TextureManager.h"
#include "Map.h"

#include "Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "AssetManager.h"
#include <sstream>

Map* map;
Manager manager;
KeyboardController input;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

AssetManager* Game::assets = new AssetManager(&manager);
bool Game::isRunning = false;
bool Game::shoot = false;

auto& newPlayer(manager.addEntity());
auto& newPlayer2(manager.addEntity());
auto& wall(manager.addEntity());
auto& label(manager.addEntity());


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
		shoot = false;
		if (TTF_Init() == -1)
		{
			std::cout << "Error : SDL_TTF" << std::endl;
		}
	}
	

	//Add more according to what objects are added
	map = new Map();

	assets->AddTexture("player", "img/yeh.png");
	assets->AddTexture("wall", "img/square.png");

	assets->AddFont("arial", "font/calculator.ttf", 50);
	
	newPlayer.addComponent<TransformComponent>(10.0f,385.0f);
	newPlayer.addComponent<SpriteComponent>("player", true);
	newPlayer.addComponent<KeyboardController>();
	newPlayer.addComponent<ColliderComponent>("player");
	newPlayer.addGroup(groupPlayers);
	
	newPlayer2.addComponent<TransformComponent>(500.0f, 385.0f);
	newPlayer2.addComponent<SpriteComponent>("player", true);
	newPlayer2.addComponent<KeyboardController>();
	newPlayer2.addComponent<ColliderComponent>("player2");
	newPlayer2.addGroup(groupPlayers);

	//Change ground thickness
	wall.addComponent<TransformComponent>(0.0f, 620.0f, 50, 1280, 1);
	wall.addComponent<SpriteComponent>("wall");
	wall.addComponent<ColliderComponent>("wall");
	wall.addGroup(groupMap);

	SDL_Color black = { 0, 0, 0,0 };

	label.addComponent<UILabel>(800, 10, "Test String", "arial", black);
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
bool shoot_once = true;
void Game::update()
{
	frameStart = 60-(SDL_GetTicks()/1000);
	std::cout << frameStart << std::endl;

	cnt++;
	if (cnt%120==0)
	{
		//std::cout << cnt << std::endl;
	}
	
	Vector2D playerPos = newPlayer.getComponent<TransformComponent>().position;
	SDL_Rect playerCol = newPlayer.getComponent<ColliderComponent>().collider;
	//Add more according to what objects need to be updated
	
	std::stringstream ss;
	ss << "Player position: " << frameStart;
	label.getComponent<UILabel>().SetLabelText(ss.str(), "arial");

	if (frameStart == 0)
	{
		isRunning = false;
	}

	manager.refresh();
	manager.update();
	
	//std::cout << shoot;
	if (shoot == true)
	{
		std::cout << "Object created";
		assets->AddTexture("projectile", "img/b_yeh.png");
		manager.PrintEntity();
		assets->CreateProjectile(Vector2D(playerPos.x+160,playerPos.y+115), Vector2D(2, 0), 200, 1, "projectile");
		/*
		assets->AddTexture("projectile", "img/b_yeh.png");
		assets->CreateProjectile(Vector2D(200, 500), Vector2D(2, 0), 200, 1, "projectile");
		*/
		shoot = false;
	}

	//assets->CreateProjectile(Vector2D(600, 600), Vector2D(2, 0), 200, 2, "projectile");
	/*
	for (auto& c : colliders)
	{
		SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
		if (Collision::CollisionDetect(cCol, playerCol))
		{
			std::cout << "hit" << std::endl;
			newPlayer.getComponent<TransformComponent>().position = playerPos;
		}
	}
	*/
	//std::cout <<"Player" << newPlayer.getComponent<ColliderComponent>().collider.x << ", " << newPlayer.getComponent<ColliderComponent>().collider.y << std::endl;
	int count = 0;
	for (auto& p : projectiles)
	{
		count++;
		//std::cout <<"Projectile: "<< p->getComponent<ColliderComponent>().collider.x << ", " << p->getComponent<ColliderComponent>().collider.y << std::endl;
		if (Collision::CollisionDetect(newPlayer.getComponent<ColliderComponent>().collider, p->getComponent<ColliderComponent>().collider))
		{
			std::cout << "Hit player1!" << std::endl;
			p->destroy();

		}
		if (Collision::CollisionDetect(newPlayer2.getComponent<ColliderComponent>().collider, p->getComponent<ColliderComponent>().collider))
		{
			std::cout << "Hit player2!" << std::endl;
			p->destroy();

		}
	}

	//std::cout << count << std::endl;
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
	for (auto& pr : projectiles)
	{
		pr->draw();
	}


	label.draw();
	SDL_RenderPresent(renderer);
}
void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	//std::cout << "Game Cleaned" << std::endl;

}