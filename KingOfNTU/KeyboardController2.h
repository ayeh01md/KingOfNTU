#pragma once
#include "Game.h"
#include "ECS.h"
#include "Components.h"
#include "GameObject.h"

class KeyboardController2 :public Component
{
public:
	TransformComponent* transform;
	SpriteComponent* sprite;
	BulletSpriteComponent* bullet;
	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
		bullet = &entity->getComponent<BulletSpriteComponent>();
	}

	void update() override
	{
		if (Game::event.type == SDL_KEYDOWN)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_UP:
				transform->velocity.y = -10;
				transform->up = true;
				sprite->animated = true;
				break;
			case SDLK_LEFT:
				transform->velocity.x = -5;
				sprite->isright = false;
				sprite->animated = true;
				break;
			case SDLK_DOWN:
				transform->velocity.y = 5;
				sprite->animated = true;
				break;
			case SDLK_RIGHT:
				transform->velocity.x = 5;
				sprite->isright = true;
				sprite->animated = true;
				break;
			case SDLK_l:
				if (!bullet->isfly)bullet->fire = true;
				bullet->get = false;
				break;
			
			default:
				break;
			}
		}

		if (Game::event.type == SDL_KEYUP)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_UP:
				transform->velocity.y = 3;
				transform->up = false;
				sprite->animated = false;
				break;
			case SDLK_LEFT:
				transform->velocity.x = 0;
				sprite->animated = false;

				break;
			case SDLK_DOWN:
				transform->velocity.y = 3;
				sprite->animated = false;
				break;
			case SDLK_RIGHT:
				transform->velocity.x = 0;
				sprite->animated = false;
				break;
			default:
				break;
			}
		}
	}



};