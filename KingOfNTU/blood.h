#pragma once
#include"TextureManager.h"


class blood {
public:
	blood( int p1hp) {
		drawScene( p1hp);
	}
	void drawScene( int p1hp) {

		srcRect.h = 43;
		srcRect.w = 455;
		srcRect.x = 0;
		srcRect.y = 0;

		destRect.x = 73;
		destRect.y = 64;
		destRect.w = srcRect.w;//Size of character?
		destRect.h = srcRect.h;
		objTexture = TextureManager::LoadTexture("img/redblood.png");
	}

	void Render(int p1hp) {


		destRect.w = int(double(srcRect.w) * (double(p1hp) / 100.0));//Size of character?

		//std::cout << p1destRect.w << std::endl;
		SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);


		//SDL_RenderCopy(Game::renderer, p2hptext, &p2srcRect, &p2destRect);
	}
private:
	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;

};