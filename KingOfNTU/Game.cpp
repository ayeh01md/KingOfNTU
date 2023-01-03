#include "Game.h"
#include "TextureManager.h"
#include "Components.h"
#include "Vector2D.h"
#include "GameScene.h"
#include "Collision.h"
#include "blood.h"
#include "blood2.h"
#include <sstream>
Manager manager;

GameScene* scene;
blood* p1blood;
blood2* p2blood;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
AssetManager* Game::assets = new AssetManager(&manager);

bool Game::p1shoot = false;
bool Game::p2shoot = false;
auto& newPlayer(manager.addEntity());
auto& newPlayer2(manager.addEntity());
auto& label(manager.addEntity());




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
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}
		isRunning = true;
		if (TTF_Init() == -1)
		{
			std::cout << "Error : SDL_TTF" << std::endl;
		}
	}
	/*
	SDL_Surface* tmpSurface = IMG_Load("img/yeh.png");
	playerTex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	*/

	//Add more according to what objects are added


	assets->AddTexture("player1", p1path);
	assets->AddTexture("player2", p2path);
	assets->AddFont("arial", "font/calculator.ttf", 100);



	scene = new GameScene(3);
	p1blood = new blood(p1hp);
	p2blood = new blood2(p2hp);

	newPlayer.addComponent<TransformComponent>(100 , 0);
	newPlayer.addComponent<SpriteComponent>("player1" , false);
	newPlayer.addComponent<KeyboardController1>();
	newPlayer.addComponent<ColliderComponent>("player1");
	newPlayer.addGroup(groupPlayers);


	newPlayer2.addComponent<TransformComponent>(1000 , 0);
	newPlayer2.addComponent<SpriteComponent>("player2" , false);
	newPlayer2.addComponent<KeyboardController2>();
	newPlayer2.addComponent<ColliderComponent>("player2");
	newPlayer2.addGroup(groupPlayers);



	SDL_Color black = { 0, 0, 0,0 };

	label.addComponent<UILabel>(595, 50, "Test String", "arial", black);	
}


auto& players(manager.getGroup(Game::groupPlayers));
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
	frameStart = 60 - (SDL_GetTicks() / 1000);
	std::cout << frameStart << std::endl;


	Vector2D playerPos = newPlayer.getComponent<TransformComponent>().position;
	SDL_Rect playerCol = newPlayer.getComponent<ColliderComponent>().collider;
	//Add more according to what objects need to be updated

	Vector2D playerPos2 = newPlayer2.getComponent<TransformComponent>().position;
	SDL_Rect playerCol2 = newPlayer2.getComponent<ColliderComponent>().collider;

	std::stringstream ss;
	ss << frameStart;
	label.getComponent<UILabel>().SetLabelText(ss.str(), "arial");


	manager.refresh();
	manager.update();

	//std::cout << shoot;
	if (p1shoot == true)
	{
		std::cout << "Object created";
		assets->AddTexture("projectile", p1bpath);
		manager.PrintEntity();
	if(newPlayer.getComponent<SpriteComponent>().isright)assets->CreateProjectile(Vector2D(playerPos.x + 200, playerPos.y + 115), Vector2D(10, 0), 50, 1, "projectile" , h1 ,w1);
	else assets->CreateProjectile(Vector2D(playerPos.x - 150, playerPos.y + 115), Vector2D(-10, 0), 50, 1, "projectile" , h1 , w1);
		/*
		assets->AddTexture("projectile", "img/b_yeh.png");
		assets->CreateProjectile(Vector2D(200, 500), Vector2D(2, 0), 200, 1, "projectile");
		*/
		p1shoot = false;
	}

	if (p2shoot == true)
	{
		std::cout << "Object created";
		assets->AddTexture("projectile2", p2bpath);
		manager.PrintEntity();
		if (newPlayer2.getComponent<SpriteComponent>().isright)assets->CreateProjectile(Vector2D(playerPos2.x + 200, playerPos2.y + 115), Vector2D(10, 0), 50, 1, "projectile2" , h2 , w2);
		else assets->CreateProjectile(Vector2D(playerPos2.x - 150, playerPos2.y + 115), Vector2D(-10, 0), 50, 1, "projectile2" , h2, w2);
		/*
		assets->AddTexture("projectile", "img/b_yeh.png");
		assets->CreateProjectile(Vector2D(200, 500), Vector2D(2, 0), 200, 1, "projectile");
		*/
		p2shoot = false;
	}


	int count = 0;
	for (auto& p : projectiles)
	{
		count++;
		//std::cout <<"Projectile: "<< p->getComponent<ColliderComponent>().collider.x << ", " << p->getComponent<ColliderComponent>().collider.y << std::endl;
		if (Collision::CollisionDetect(newPlayer.getComponent<ColliderComponent>().collider, p->getComponent<ColliderComponent>().collider))
		{
			std::cout << "Hit player1!" << std::endl;
			p->destroy();
			p1hp -= 10;

		}
		if (Collision::CollisionDetect(newPlayer2.getComponent<ColliderComponent>().collider, p->getComponent<ColliderComponent>().collider))
		{
			std::cout << "Hit player2!" << std::endl;
			p->destroy();
			p2hp -= 10;

		}
	}


}

void Game::render()
{

	SDL_RenderClear(renderer);
	//SDL_RenderCopy(renderer, playerTex, NULL, &destR);
	// 
	//Add more according to what objects need to be rendered
	if (p1hp <= 0 || p2hp <= 0 || frameStart <=0)   {
		scene->drawScene(4);
		scene->Render();
		p1blood->Render(0);
		p2blood->Render(0);
		SDL_RenderPresent(renderer);
		return;
	}
	scene->Render();
	p1blood->Render(p1hp);
	p2blood->Render(p2hp);

	manager.draw();

	for (auto& p : players)
	{
		p->draw();
	}
	for (auto& pr : projectiles)
	{
		std::cout << "asd" << std::endl;
		pr->draw();
	}
	

	label.draw();
	
	SDL_RenderPresent(renderer);
	//label.draw();
}
void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned" << std::endl;

}