#pragma once
extern SDL_Renderer* gRenderer;
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

class LWindow
{
public:
    LWindow();

    bool init();

    SDL_Renderer* createRenderer();

    void handleEvent(SDL_Event& e);

    void free();

    int getWidth();
    int getHeight();

    bool isMinimized();

private:
    SDL_Window* mWindow;

    int mWidth;
    int mHeight;
    bool mFullScreen;
    bool mMinimized;
};
extern LWindow gWindow;

