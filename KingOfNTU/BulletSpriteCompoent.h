#pragma once
#include "Components.h"
#include "SDL.h"
#include "TextureManager.h"
#include "SDL_ttf.h"
//#include "GameObject.h"

class BulletSpriteComponent : public Component
{
private:
	TransformComponent* transform;
	SpriteComponent* sprite;
	SDL_Texture* texture;
	


public:
	BulletSpriteComponent() = default;
	BulletSpriteComponent(const char* path)
	{
		setTex(path);
	}

	void setTex(const char* path)
	{
		texture = TextureManager::LoadTexture(path);
		//std::cout<<"shot!!"<<std::endl;
	}

	void init() override
	{
		std::cout << "init sucss" << std::endl;
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();

		srcRect.x = 0;
		srcRect.y = 0;

		srcRect.w = 60;
		srcRect.h = 24;

		destRect.w = 60;
		destRect.h = 24;



	}
	void checkout() 
	{
		if (destRect.x > 1280 || destRect.x < 0) {
			fire = false;
		}
	}

	void getcurpos() {
		if (get) return;
		destRect.x = (int)transform->position.x;
		destRect.y = (int)transform->position.y +50;
		get = true;
		curisright = sprite->isright;
	}

	void update() override
	{	
		
		if (fire) {
			getcurpos();
			if (curisright)destRect.x += 30;
			else destRect.x -= 30;
			if (destRect.x < -100 || destRect.x > 1300) {
				fire = false;
				isfly = false;
			}
		}

		//destRect.x = (int)transform->position.x;
		

	}	

	void draw() override
	{
		//std::cout << "draw bullet" << std::endl;
		TextureManager::Draw(texture, srcRect, destRect);
	}
	int velocity = 0;
	SDL_Rect srcRect, destRect;
	bool curisright = true;
	bool fire = false;
	bool isfly = false;
	bool get = false;
	int curx;
	int cury;
};


