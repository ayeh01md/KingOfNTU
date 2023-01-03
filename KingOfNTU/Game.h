#pragma once

#include"SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>

class AssetManager;
class ColliderComponent;

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	bool running() { return isRunning; }
	void render();
	void clean();

	static SDL_Renderer* renderer;
	static SDL_Event event;
	static bool p1shoot;
	static bool p2shoot;
	static bool isRunning;
	static AssetManager* assets;
	enum groupLabels : std::size_t
	{
		groupMap,
		groupPlayers,
		groupColliders,
		groupEnemies,
		groupProjectiles
	};

private:
	SDL_Window* window;
	Uint32 frameStart;
	int frameTime;
	const char* p1path;
	const char* p1bpath;
	const char* p2path;
	const char* p2bpath;
	int p1hp = 100;
	int p2hp = 100;
};




