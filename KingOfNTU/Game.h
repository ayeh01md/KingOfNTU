#pragma once

#include"SDL.h"
#include "SDL_image.h"
#include <iostream>

class Game
{
public:
	Game(int p1, int p2){
		if (p1 == 1) {
			p1path = "img/yeh.png";
			p1bpath = "img/b_yeh.png";
		}
		if (p1 == 2) {
			p1path = "img/david.png";
			p1bpath = "img/b_david.png";
		}
		if (p1 == 3) {
			p1path = "img/yang.png";
			p1bpath = "img/b_yang.png";
		}
		if (p1 == 4) {
			p1path = "img/huang.png";
			p1bpath = "img/b_huang.png";
		}
		if (p1 == 5) {
			p1path = "img/article.png";
			p1bpath = "img/b_article.png";
		}
		if (p1 == 6) {
			p1path = "img/li.png";
			p1bpath = "img/b_li.png";
		}

		if (p2 == 1) {
			p2path = "img/yeh.png";
			p2bpath = "img/b_yeh.png";
		}
		if (p2 == 2) {
			p2path = "img/david.png";
			p2bpath = "img/b_david.png";
		}
		if (p2 == 3) {
			p2path = "img/yang.png";
			p2bpath = "img/b_yang.png";
		}
		if (p2 == 4) {
			p2path = "img/huang.png";
			p2bpath = "img/b_huang.png";
		}
		if (p2 == 5) {
			p2path = "img/article.png";
			p2bpath = "img/b_article.png";
		}
		if (p2 == 6) {
			p2path = "img/li.png";
			p2bpath = "img/b_li.png";
		}

	}
	~Game() {};

	void init(const char* title, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	bool running() { return isRunning; }
	void render();
	void clean();

	static SDL_Renderer* renderer;
	static SDL_Event event;

private:
	bool isRunning = false;
	int cnt = 0;
	SDL_Window* window;
	const char* p1path;
	const char* p1bpath;
	const char* p2path;
	const char* p2bpath;
	int p1hp = 100;
	int p2hp = 100;

};



