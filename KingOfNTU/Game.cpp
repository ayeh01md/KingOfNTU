#include "Game.h"
#include "TextureManager.h"
#include "Components.h"
#include "Vector2D.h"
#include "GameScene.h"
#include "Collision.h"
#include "blood.h"
#include "blood2.h"
Manager manager;

GameScene* scene;
blood* p1blood;
blood2* p2blood;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

auto& newPlayer(manager.addEntity());
auto& newPlayer2(manager.addEntity());



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
	}
	/*
	SDL_Surface* tmpSurface = IMG_Load("img/yeh.png");
	playerTex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	*/

	//Add more according to what objects are added
	scene = new GameScene(3);
	p1blood = new blood(p1hp);
	p2blood = new blood2(p2hp);

	newPlayer.addComponent<TransformComponent>(100 , 0);
	newPlayer.addComponent<SpriteComponent>(p1path);
	newPlayer.addComponent<BulletSpriteComponent>(p1bpath);
	newPlayer.addComponent<KeyboardController1>();
	newPlayer.addComponent<ColliderComponent>("player");

	newPlayer2.addComponent<TransformComponent>(1000 , 0);
	newPlayer2.addComponent<SpriteComponent>(p2path);
	newPlayer2.addComponent<BulletSpriteComponent>(p2bpath);
	newPlayer2.addComponent<KeyboardController2>();
	newPlayer2.addComponent<ColliderComponent>("player2");
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
	


	if (newPlayer.getComponent<BulletSpriteComponent>().fire) {
		std::cout << "fire" << std::endl;
		if (Collision::CollisionDetect(newPlayer2.getComponent<ColliderComponent>().collider, newPlayer.getComponent<BulletSpriteComponent>().destRect))
		{
			std::cout << "Hit player2!" << std::endl;
			p2hp--;
			std::cout << p2hp << std::endl;
		}
			
	}

	if (newPlayer2.getComponent<BulletSpriteComponent>().fire) {
		std::cout << "fire" << std::endl;
		if (Collision::CollisionDetect(newPlayer.getComponent<ColliderComponent>().collider, newPlayer2.getComponent<BulletSpriteComponent>().destRect))
		{
			
			std::cout << "Hit player1!" << std::endl;
			p1hp--;
			std::cout << p1hp << std::endl;
		}

	}
	




	//std::cout <<"p1 : " << newPlayer.getComponent<TransformComponent>().position.x << "," << newPlayer.getComponent<TransformComponent>().position.y << std::endl;
	//std::cout <<"p2 : " << newPlayer2.getComponent<TransformComponent>().position.x << "," << newPlayer2.getComponent<TransformComponent>().position.y << std::endl;

}

void Game::render()
{

	SDL_RenderClear(renderer);
	//SDL_RenderCopy(renderer, playerTex, NULL, &destR);
	// 
	//Add more according to what objects need to be rendered
	if (p1hp <= 0 || p2hp <= 0) {
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
	
	SDL_RenderPresent(renderer);
}
void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned" << std::endl;

}