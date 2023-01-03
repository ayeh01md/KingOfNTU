#pragma once
#include "Game.h"
#include "ECS.h"
#include "Components.h"


class KeyboardController2 :public Component
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
			case SDLK_UP:
				transform->velocity.y = -1;
				break;
			case SDLK_LEFT:
				transform->velocity.x = -1;
				sprite->Play("Left");
				break;
			case SDLK_DOWN:
				transform->velocity.y = 1;
				break;
			case SDLK_RIGHT:
				transform->velocity.x = 1;
				sprite->Play("Right");
				break;
			case SDLK_l:
				Game::p2shoot = true;
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
				transform->velocity.y = 0;
				break;
			case SDLK_LEFT:
				transform->velocity.x = 0;
				break;
			case SDLK_DOWN:
				transform->velocity.y = 0;
				break;
			case SDLK_RIGHT:
				transform->velocity.x = 0;
				break;
			case SDLK_ESCAPE:
				Game::isRunning = false;
			default:
				break;
			}
		}
	}



};