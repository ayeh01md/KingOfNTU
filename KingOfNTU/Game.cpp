#include "Game.h"
#include "TextureManager.h"
#include "Map.h"

#include "Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "AssetManager.h"
#include <sstream>

#include "GameScene.h"
#include "blood.h"
#include "blood2.h"

Map* map;
Manager manager;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
blood* p1blood;
blood2* p2blood;

AssetManager* Game::assets = new AssetManager(&manager);
GameScene* scene;
bool Game::isRunning = false;
bool Game::p1shoot = false;
bool Game::p2shoot = false;

auto& newPlayer(manager.addEntity());
auto& newPlayer2(manager.addEntity());

//Boundaries:Left, Right, Up and Down
auto& wall1(manager.addEntity());
auto& wall2(manager.addEntity());
auto& wall3(manager.addEntity());
auto& wall4(manager.addEntity());

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
		if (TTF_Init() == -1)
		{
			std::cout << "Error : SDL_TTF" << std::endl;
		}
	}
	

	//Add more according to what objects are added
	scene = new GameScene(3);
	p1blood = new blood(p1hp);
	p2blood = new blood2(p2hp);

	assets->AddTexture("player", "img/yeh.png");
	assets->AddTexture("wall", "img/square.png");

	//Time
	assets->AddFont("arial", "font/calculator.ttf", 100);
	
	newPlayer.addComponent<TransformComponent>(10.0f,385.0f);
	newPlayer.addComponent<SpriteComponent>("player", true);
	newPlayer.addComponent<KeyboardController1>();
	newPlayer.addComponent<ColliderComponent>("player");
	newPlayer.addGroup(groupPlayers);
	
	newPlayer2.addComponent<TransformComponent>(500.0f, 385.0f);
	newPlayer2.addComponent<SpriteComponent>("player", true);
	newPlayer2.addComponent<KeyboardController2>();
	newPlayer2.addComponent<ColliderComponent>("player2");
	newPlayer2.addGroup(groupPlayers);

	//Left Wall
	wall1.addComponent<TransformComponent>(0.0f, 0.0f, 720, 0, 1);
	wall1.addComponent<ColliderComponent>("wall");
	wall1.addGroup(groupColliders);

	//Right Wall
	wall2.addComponent<TransformComponent>(1280.0f, 0.0f, 720, 0, 1);
	wall2.addComponent<ColliderComponent>("wall");
	wall2.addGroup(groupColliders);

	//Ceiling
	wall3.addComponent<TransformComponent>(0.0f, 0.0f, 0, 1280, 1);
	wall3.addComponent<ColliderComponent>("wall");
	wall3.addGroup(groupColliders);

	//Floor
	wall4.addComponent<TransformComponent>(0.0f, 650.0f, 10, 1280, 1);
	wall4.addComponent<SpriteComponent>("wall", false);
	wall4.addComponent<ColliderComponent>("wall");
	wall4.addGroup(groupColliders);

	SDL_Color black = { 0, 0, 0,0 };

	//Time add
	label.addComponent<UILabel>(610, 10, "Test String", "arial", black);
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
	//CalculateTime
	frameStart = 60-(SDL_GetTicks()/1000);
	std::cout << frameStart << std::endl;

	
	Vector2D playerPos1 = newPlayer.getComponent<TransformComponent>().position;
	Vector2D playerPos2 = newPlayer2.getComponent<TransformComponent>().position;
	SDL_Rect playerCol1 = newPlayer.getComponent<ColliderComponent>().collider;
	SDL_Rect playerCol2 = newPlayer2.getComponent<ColliderComponent>().collider;
	//Add more according to what objects need to be updated
	
	//Display Time
	std::stringstream ss;
	ss << frameStart;
	label.getComponent<UILabel>().SetLabelText(ss.str(), "arial");

	if (frameStart == 0)
	{
		isRunning = false;
	}

	manager.refresh();
	manager.update();
	
	for (auto& c : colliders)
	{
		SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
		if (Collision::CollisionDetect(cCol, playerCol1))
		{
			std::cout << "hit" << std::endl;
			newPlayer.getComponent<TransformComponent>().position.x = playerPos1.x;
		}
	}

	for (auto& c : colliders)
	{
		SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
		if (Collision::CollisionDetect(cCol, playerCol2))
		{
			std::cout << "hit" << std::endl;
			newPlayer2.getComponent<TransformComponent>().position.x = playerPos2.x;
		}
	}


	//std::cout << shoot;
	if (p1shoot == true)
	{
		std::cout << "Object created";
		assets->AddTexture("projectile", "img/b_yeh.png");
		manager.PrintEntity();
		assets->CreateProjectile(Vector2D(playerPos1.x+160,playerPos1.y+115), Vector2D(2, 0), 200, 1, "projectile");
		/*
		assets->AddTexture("projectile", "img/b_yeh.png");
		assets->CreateProjectile(Vector2D(200, 500), Vector2D(2, 0), 200, 1, "projectile");
		*/
		p1shoot = false;
	}

	if (p2shoot == true)
	{
		std::cout << "Object created";
		assets->AddTexture("projectile", "img/b_yeh.png");
		manager.PrintEntity();
		assets->CreateProjectile(Vector2D(playerPos2.x + 160, playerPos2.y + 115), Vector2D(2, 0), 200, 1, "projectile");
		/*
		assets->AddTexture("projectile", "img/b_yeh.png");
		assets->CreateProjectile(Vector2D(200, 500), Vector2D(2, 0), 200, 1, "projectile");
		*/
		p2shoot = false;
	}


	for (auto& p : projectiles)
	{
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
	for (auto& c : colliders)
	{
		c->draw();
	}
	for (auto& p : players)
	{
		p->draw();
	}
	for (auto& pr : projectiles)
	{
		pr->draw();
	}

	
	//Display TIme
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