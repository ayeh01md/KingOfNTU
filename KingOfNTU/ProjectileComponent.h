/*
#pragma once

#include "Components.h"
#include "SDL.h"

class ProjectileComponent : public Component
{
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	int speed = 5;
	Vector2D velocity;

public:
	ProjectileComponent() = default;
	ProjectileComponent(const char* path)
	{
		setTex(path);
	}

	void setTex(const char* path)
	{
		texture = TextureManager::LoadTexture(path);
	}

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		transform->velocity = velocity;

		srcRect.x = 0;
		srcRect.y = 0;

		srcRect.w = 30;
		srcRect.h = 12;

		destRect.w = 30;
		destRect.h = 12;
	}

	void update() override
	{
		if (transform->position.x > 1280)
		{
			entity->destroy();
		}
		else
		{
			destRect.x = (int)transform->position.x;
			destRect.y = (int)transform->position.y;
		}

	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect);
	}

};
*/