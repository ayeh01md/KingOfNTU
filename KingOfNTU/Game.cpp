#include "Game.h"
#include "TextureManager.h"
#include "Components.h"
#include "Vector2D.h"
#include "GameScene.h"
#include "Collision.h"
#include "blood.h"
#include "blood2.h"
#include <sstream>
#include "SDL_ttf.h"
#include "SDL_mixer.h"

Manager manager;

GameScene* scene;
blood* p1blood;
blood2* p2blood;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
AssetManager* Game::assets = new AssetManager(&manager);
Mix_Chunk* gShoot = NULL;
bool Game::p1shoot = false;
bool Game::p2shoot = false;
bool Game::isRunning = false;
auto& newPlayer(manager.addEntity());
auto& newPlayer2(manager.addEntity());
auto& label(manager.addEntity());
auto& label2(manager.addEntity());



void Game::init(const char* title, int width, int height, bool fullscreen)
{
	int flags = 0;
	curticks = SDL_GetTicks();
	if (fullscreen)
	{
		flags = SDL_WINDOW_MAXIMIZED;
	}
	
	isRunning = true;
	if (TTF_Init() == -1)
	{
		std::cout << "Error : SDL_TTF" << std::endl;
	}
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
	}
	gShoot = Mix_LoadWAV("sound/BADNTU.wav");
	if (gShoot == NULL)
	{
		printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
	}
	

	//Texture and Font path initialization
	assets->AddTexture("player1", p1path);
	assets->AddTexture("player2", p2path);
	assets->AddFont("arial", "font/NotoSans-SemiCondensedBlack.ttf", 80);
	assets->AddFont("arial2", "font/NotoSans-SemiCondensedBlack.ttf", 50);


	scene = new GameScene(3);
	p1blood = new blood(p1hp);
	p2blood = new blood2(p2hp);

	//Add necessary components for Player 1
	newPlayer.addComponent<TransformComponent>(100 , 300);
	newPlayer.addComponent<SpriteComponent>("player1" , false);
	newPlayer.addComponent<KeyboardController1>();
	newPlayer.addComponent<ColliderComponent>("player1");
	newPlayer.addGroup(groupPlayers);

	//Add necessary components for Player 2
	newPlayer2.addComponent<TransformComponent>(1000 , 300);
	newPlayer2.addComponent<SpriteComponent>("player2" , false);
	newPlayer2.addComponent<KeyboardController2>();
	newPlayer2.addComponent<ColliderComponent>("player2");
	newPlayer2.addGroup(groupPlayers);


	//Setup for label
	SDL_Color black = { 0, 0, 0,0 };
	label.addComponent<UILabel>(595, 50, "Test String", "arial", black);
}

//Create Entity Groups 
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
		
	frameStart = 60 - ((SDL_GetTicks() -curticks) / 1000);
	std::cout << frameStart << std::endl;

	//Player1 collision size and position
	Vector2D playerPos = newPlayer.getComponent<TransformComponent>().position;
	SDL_Rect playerCol = newPlayer.getComponent<ColliderComponent>().collider;

	//Player2 collision size and position 
	Vector2D playerPos2 = newPlayer2.getComponent<TransformComponent>().position;
	SDL_Rect playerCol2 = newPlayer2.getComponent<ColliderComponent>().collider;

	//Output time
	std::stringstream ss;
	ss << frameStart;
	label.getComponent<UILabel>().SetLabelText(ss.str(), "arial");


	manager.refresh();
	manager.update();

	//Creation of projectiles from player1
	if (p1shoot == true)
	{
		Mix_PlayChannel(-1, gShoot, 0);
		std::cout << "Object created";
		assets->AddTexture("projectile", p1bpath);
		manager.PrintEntity();
	if(newPlayer.getComponent<SpriteComponent>().isright)assets->CreateProjectile(Vector2D(playerPos.x + 200, playerPos.y + 115), Vector2D(10, 0), 50, 1, "projectile" , h1 ,w1);
	else assets->CreateProjectile(Vector2D(playerPos.x - 150, playerPos.y + 115), Vector2D(-10, 0), 50, 1, "projectile" , h1 , w1);
		p1shoot = false;
	}

	//Creation of projectiles from player2
	if (p2shoot == true)
	{
		Mix_PlayChannel(-1, gShoot, 0);
		std::cout << "Object created";
		assets->AddTexture("projectile2", p2bpath);
		manager.PrintEntity();
		if (newPlayer2.getComponent<SpriteComponent>().isright)assets->CreateProjectile(Vector2D(playerPos2.x + 200, playerPos2.y + 115), Vector2D(10, 0), 50, 1, "projectile2" , h2 , w2);
		else assets->CreateProjectile(Vector2D(playerPos2.x - 150, playerPos2.y + 115), Vector2D(-10, 0), 50, 1, "projectile2" , h2, w2);
		p2shoot = false;
	}


	for (auto& p : projectiles)
	{
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

	if (p1hp <= 0 || p2hp <= 0 || frameStart <= 0) {
		scene->drawScene(4);
	}


}

void Game::render()
{

	SDL_RenderClear(renderer);
	//check if the game end
	if (p1hp <= 0 || p2hp <= 0 || frameStart <=0)   {
		//set scene
		scene->Render();
		p1blood->Render(0);
		p2blood->Render(0);
		
		//print which player win
		SDL_Color black = { 0, 0, 0,0 };
		if(p1hp <= 0 )label2.addComponent<UILabel>(450, 450, "Player 2 WIN!!", "arial2", black);
		else if (p2hp <= 0)label2.addComponent<UILabel>(450, 450, "Player 1 WIN!!", "arial2", black);
		else if(p1hp < p2hp)label2.addComponent<UILabel>(450, 450, "Player 2 WIN!!", "arial2", black);
		else if(p1hp > p2hp)label2.addComponent<UILabel>(450, 450, "Player 1 WIN!!", "arial2", black);
		else label2.addComponent<UILabel>(450, 450, "Player  TIE!!", "arial2", black);
		label2.draw();
		Mix_HaltMusic();
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
}
void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	TTF_Quit();
	IMG_Quit();
	Mix_Quit();
	SDL_Quit();
	std::cout << "Game Cleaned" << std::endl;

}