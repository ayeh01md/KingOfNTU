#pragma once
#include "Components.h"
#include "SDL.h"
#include "TextureManager.h" 
//#include "GameObject.h"

class SpriteComponent : public Component
{
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

	
	int frames = 0;
	int speed = 100;

public:
	SpriteComponent() = default;
	SpriteComponent(const char* path)
	{
		setTex(path);
	}

	void setTex(const char* path)
	{
		animated = false;
		frames = 4;
		speed = 100;
		texture = TextureManager::LoadTexture(path);
	}

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = 0;
		srcRect.y = 0;

		srcRect.w = 160;
		srcRect.h = 235;

		destRect.w = 160;
		destRect.h = 235;
	}

	void update() override
	{
		if (animated) {
			if(isright)srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
			else srcRect.x = srcRect.w * (static_cast<int>((SDL_GetTicks() / speed) % frames  +5));
		}
		else {
			if (isright) srcRect.x = srcRect.w;
			else srcRect.x = srcRect.w * 5;
		}

		destRect.x = (int)transform->position.x;
		destRect.y = (int)transform->position.y;
	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect);
	}
	bool animated = false;
	bool isright = true;
};