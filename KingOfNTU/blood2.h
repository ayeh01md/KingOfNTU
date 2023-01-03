#pragma once
#include"TextureManager.h"


class blood2 {
public:
	blood2(int p2hp) {
		drawScene(p2hp);
	}
	void drawScene(int p2hp) {

		srcRect.h = 43;
		srcRect.w = 455;
		srcRect.x = 0;
		srcRect.y = 0;

		destRect.x = 753;
		destRect.y = 64;
		destRect.w = srcRect.w;//Size of character?
		destRect.h = srcRect.h;
		objTexture = TextureManager::LoadTexture("img/redblood.png");
	}

	void Render(int p2hp) {


		destRect.w = int(double(srcRect.w) * (double(p2hp) / 100.0));//Size of character?
		//std::cout << p1destRect.w << std::endl;
		SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);


		//SDL_RenderCopy(Game::renderer, p2hptext, &p2srcRect, &p2destRect);
	}
private:
	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;

}; 
