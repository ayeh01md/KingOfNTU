#pragma once
#include "Game.h"
#include "ECS.h"
#include "Components.h"

class KeyboardController1 :public Component
{
public:
	TransformComponent* transform;
	SpriteComponent* sprite;
	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}

	void update() override
	{
		if (Game::event.type == SDL_KEYDOWN)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = -10;
				transform->up = true;
				sprite->animated = true;
				break;
			case SDLK_a:
				transform->velocity.x = -5;
				sprite->isright = false;
				sprite->animated = true;
				sprite->Play("Left");
				break;
			case SDLK_s:
				transform->velocity.y = 10;
				sprite->animated = true;
				break;
			case SDLK_d:
				transform->velocity.x = 5;
				sprite->isright = true;
				sprite->animated = true;
				sprite->Play("Right");
				break;
			case SDLK_t:
				Game::p1shoot = true;
				break;
			case SDLK_f:
				if(sprite->isright)transform->position.x += 300;
			else transform->position.x -= 300;
				break;
			default:
				break;
			}
		}

		if (Game::event.type == SDL_KEYUP)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = 3;
				transform->up = false;
				sprite->animated = false;
				break;
			case SDLK_a:
				transform->velocity.x = 0;
				sprite->animated = false;
				break;
			case SDLK_s:
				transform->velocity.y = 3;
				sprite->animated = false;
				break;
			case SDLK_d:
				transform->velocity.x = 0;
				sprite->animated = false;
				break;
			default:
				break;
			}
		}
	}



};