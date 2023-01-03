#pragma once
#include "Components.h"
#include"Vector2D.h"

class TransformComponent :public Component
{
private:
	const int WINDOW_LENGTH = 1280;
	const int WINDOW_HEIGHT = 720;
public:

	Vector2D position;
	Vector2D velocity;
	int speed = 3;
	bool up = false;
	int height = 235;
	int width = 160;
	int scale = 1;
	TransformComponent()
	{
		position.x = 0.0f;
		position.y = 0.0f;
	}

	TransformComponent(int x, int y)
	{
		position.x = x;
		position.y = y;
	}

	TransformComponent(float x, float y, int h, int w, int sc)
	{
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
	}

	void init() override
	{
		velocity.x = 0;
		velocity.y = 0;
	}

	void update() override
	{
		if (position.x < -150 ) {
			position.x = -149;
		}
		else if (position.x > 1280) {
			position.x = 1279;
		}
		else if (position.y < -100) {
			position.y = -99;
		}
		else position.x += velocity.x * speed;

		if (position.y > 450) {
			if (up)position.y += velocity.y * speed;
			else return;
		}
		position.y += velocity.y * speed;
		
	
	
	}
};