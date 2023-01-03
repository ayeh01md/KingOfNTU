#pragma once
#include"TextureManager.h"


class GameScene {
public:
	GameScene(int num ){
		drawScene(num);
	}
	void drawScene(int num ) {

		srcRect.h = 720;
		srcRect.w = 1280;
		srcRect.x = 0;
		srcRect.y = 0;

		destRect.x = 0;
		destRect.y = 0;
		destRect.w = srcRect.w;//Size of character?
		destRect.h = srcRect.h;
		


		switch (num)
		{
		case 3:
			objTexture = TextureManager::LoadTexture(fight);
			//p1hptext = TextureManager::LoadTexture("img/whiteblood.png");
			//p2hptext = TextureManager::LoadTexture(blood);
			break;
		case 4:
			objTexture = TextureManager::LoadTexture(over);
			break;
		default:
			break;
		}
	}

	void Render() {



		//p1destRect.w = int(double(p1srcRect.w) * (double(p1hp) / 100.0));//Size of character?

		//std::cout << p1destRect.w << std::endl;
		//SDL_RenderCopy(Game::renderer, p1hptext, &p1srcRect, &p1destRect);
		SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
		

		//SDL_RenderCopy(Game::renderer, p2hptext, &p2srcRect, &p2destRect);
	}
private:
	const char* fight = "img/fightpage.png";
	const char* over = "img/gameoverpage.png";
	const char* blood = "img/square.png";
	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;



};