
#include "SDL.h"
#include "SDL_image.h"
#include <stdio.h>
#include <string>
#include "LWindow.h"

LWindow::LWindow()
{
    mWindow = NULL;
    mFullScreen = false;
    mMinimized = false;
    mWidth = 0;
    mHeight = 0;
}

bool LWindow::init()
{
    mWindow = SDL_CreateWindow("King of NTU", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_MAXIMIZED);
    if (mWindow != NULL)
    {
        mWidth = SCREEN_WIDTH;
        mHeight = SCREEN_HEIGHT;
    }

    return mWindow != NULL;
}

SDL_Renderer* LWindow::createRenderer()
{
    return SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

void LWindow::handleEvent(SDL_Event& e)
{
    if (e.type == SDL_WINDOWEVENT)
    {
        switch (e.window.event)
        {
        case SDL_WINDOWEVENT_SIZE_CHANGED:
            mWidth = e.window.data1;
            mHeight = e.window.data2;
            SDL_RenderPresent(gRenderer);
            break;

        case SDL_WINDOWEVENT_EXPOSED:
            SDL_RenderPresent(gRenderer);
            break;

        case SDL_WINDOWEVENT_MINIMIZED:
            mMinimized = true;
            break;

        case SDL_WINDOWEVENT_MAXIMIZED:
            mMinimized = false;
            break;

        case SDL_WINDOWEVENT_RESTORED:
            mMinimized = false;
            break;
        }
    }
    else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN)
    {
        if (mFullScreen)
        {
            SDL_SetWindowFullscreen(mWindow, SDL_FALSE);
            mFullScreen = false;
        }
        else
        {
            SDL_SetWindowFullscreen(mWindow, SDL_TRUE);
            mFullScreen = true;
            mMinimized = false;
        }
    }
}

void LWindow::free()
{
    if (mWindow != NULL)
    {
        SDL_DestroyWindow(mWindow);
    }
    mWidth = 0;
    mHeight = 0;
}

int LWindow::getWidth()
{
    return mWidth;
}

int LWindow::getHeight()
{
    return mHeight;
}

bool LWindow::isMinimized()
{
    return mMinimized;
}