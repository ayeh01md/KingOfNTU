#include "SDL.h"
#include "Game.h"

Game* game = nullptr;


int main(int argc, char* argv[])
{
	//Limiting Frames
	const int FPS = 200;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	game = new Game();

	game->init("game",1280, 720, false);

	while (game->running())
	{

		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();
	return 0;

}