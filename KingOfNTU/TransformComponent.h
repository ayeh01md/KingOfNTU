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

	int height = 235;
	int width = 160;
	int scale = 1;
	bool jump = false;
	int speed = 5;

	TransformComponent()
	{
		//Use to set the position of the character
		position.Zero();
	}


	TransformComponent(float x, float y)
	{
		position.x = x;
		position.y = y;
	}
	//Constructor with with size
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
		velocity.Zero();
	}

	void update() override
	{
		position.x += velocity.x * speed;
		if (position.y > 400) {
			if (jump)position.y += velocity.y * speed;
			else return;
		}
		position.y += velocity.y * speed;
	}
};
