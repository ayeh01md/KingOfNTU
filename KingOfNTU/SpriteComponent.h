#pragma once

#include "SDL.h"
#include "TextureManager.h"
#include "Animation.h"
#include <map>
#include "AssetManager.h"

class SpriteComponent : public Component
{
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

	
	int frames = 0;
	int speed = 100;



public:
	bool animated = false;
	int animIndex = 0;
	std::map<const char*, Animation> animations;




	SpriteComponent() = default;
	SpriteComponent(std::string id)
	{
		setTex(id);
	}

	SpriteComponent(std::string id, bool isAnimated)
	{
		animated = false;
		animated = isAnimated;

		Animation right = Animation(0, 4, 60);
		Animation left = Animation(5, 4, 60);

		animations.emplace("Right", right);
		animations.emplace("Left", left);

		Play("Right");
		setTex(id);
	}

	~SpriteComponent()
	{

	}

	void setTex(std::string id)
	{
		texture = Game::assets->GetTexture(id);
	}

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = 0;
		srcRect.y = 0;



		srcRect.w = transform->width;
		srcRect.h = transform->height;

	}

	void update() override
	{
		if (animated)
		{
			srcRect.x = (animIndex * transform->width) + (srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames));
		}



		destRect.x = static_cast<int>(transform->position.x);
		destRect.y = static_cast<int>(transform->position.y);
		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;
	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect);
	}

	void Play(const char* animName)
	{
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;
	}
	bool isright = true;
};