#pragma once

#include"LTexture.h"

enum LButtonSprite
{
    BUTTON_SPRITE_MOUSE_OUT = 0,
    BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
    BUTTON_SPRITE_MOUSE_DOWN = 2,
    BUTTON_SPRITE_MOUSE_UP = 3,
};

class LButton
{
public:
    LButton(int w, int h);

    void setPosition(int x, int y);

    void handleEvent(SDL_Event& e);

    LButtonSprite mCurrentSprite;

    bool work;
private:
    SDL_Point mPosition;

    int BUTTON_WIDTH;

    int BUTTON_HEIGHT;
};



