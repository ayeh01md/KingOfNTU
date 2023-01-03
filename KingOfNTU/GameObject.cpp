#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* texturesheet, int x, int y)
{
	objTexture = TextureManager::LoadTexture(texturesheet);

	xpos = x;
	ypos = y;
}


void GameObject::Update()
{

	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	if (currentKeyStates[SDL_SCANCODE_UP])
	{
		ypos-=5;
	}
	else if (currentKeyStates[SDL_SCANCODE_DOWN])
	{
		ypos+=5;
	}
	else if (currentKeyStates[SDL_SCANCODE_LEFT])
	{
		xpos-=5;
	}
	else if (currentKeyStates[SDL_SCANCODE_RIGHT])
	{
		xpos+=5;
	}
	srcRect.h = 235;
	srcRect.w = 160;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w;//Size of character?
	destRect.h = srcRect.h;
}
void GameObject::Render()
{
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}