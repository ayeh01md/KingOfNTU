#pragma once

#include "SDL.h"
#include "TextureManager.h"

class SpriteComponent : public Component
{
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

public:
	SpriteComponent() = default;
	SpriteComponent(const char* path)
	{
		setTex(path);
	}
	~SpriteComponent()
	{
		SDL_DestroyTexture(texture);
	}

	void setTex(const char* path)
	{
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

		//srcRect.w = transform->width;
		//srcRect.h = transform->height;

	}

	void update() override
	{
		destRect.x = (int)transform->position.x;
		destRect.y = (int)transform->position.y;
		//destRect.w = transform->width * transform->scale;
		//destRect.h = transform->height * transform->scale;
	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect);
	}

};