#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include "LWindow.h"
#include "LTexture.h"
#include "LButton.h""
#include "Game.h"
#include "GetID.h"
#include <iostream>
using namespace std;

enum scenario {
    starting = 0,
    ruleintro = 1,
    playing = 2,
    choosechar = 3,
    gameover = 4,
};

SDL_Renderer* gRenderer = NULL;
TTF_Font* gFont = NULL;
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
LWindow gWindow;
LTexture test;
LTexture gSceneTexture;
LTexture StartTexture;
LTexture RuleTexture;
LTexture BackTexture;
LButton Rule(402, 151);
LButton Start(402, 151);
LButton Back(198, 113);
//Rendered texture
LTexture gTextTexture1;
LTexture gTextTexture2;
bool ruleon, starton, backon;
bool havechosen = 1;
//Game game;
bool gamemode = 1;
bool quit = 1;
//bool *getidsuccess = false;
GetID getid;
int p1 = 0, p2 = 0;


bool init()
{
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            printf("Warning: Linear texture filtering not enabled!");
        }
        if (!gWindow.init())
        {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        //Initialize SDL_ttf
        if (TTF_Init() == -1)
        {
            printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
            success = false;
        }
        else
        {
            gRenderer = gWindow.createRenderer();
            if (gRenderer == NULL)
            {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    success = false;
                }
                ////initilize character list
                //cha_List[Yeh] = new Character(Yeh,
                //    "img/yeh.png",
                //    "img/b_yeh.png");

                //cha_List[David] = new Character(David,
                //    "img/david.png",
                //    "img/b_david.png");

                //cha_List[Huang] = new Character(Huang,
                //    "img/huang.png",
                //    "img/b_huang.png");

                //cha_List[Yang] = new Character(Yang,
                //    "img/yang.png",
                //    "img/b_yang.png");

                //cha_List[Article] = new Character(Article,
                //    "img/article.png",
                //    "img/b_article.png");

                //cha_List[Li] = new Character(Li,
                //    "img/li.png",
                //    "img/b_li.png");
            }
        }
    }
    return success;
}

bool loadMedia()
{
    bool success = true;
    if (!test.loadFromFile("img/welcomepage.png"))
    {
        printf("Failed to load window texture!\n");
        success = false;
    }
    test.free();
    gFont = TTF_OpenFont("font/Calculator.ttf", 28);
    if (gFont == NULL)
    {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        success = false;
    }
    return success;
}

void putMedia(scenario s)
{
    switch (s)
    {
    case starting:
        gSceneTexture.free();
        BackTexture.free();
        gSceneTexture.loadTexture("img/welcomepage.png");
        if (!starton) StartTexture.loadFromFile("img/startbtn.png");
        else StartTexture.loadTexture2("img/startbtn.png", 401, 151); //loadTexture2 is for btn, 1 is for window
        if (!ruleon) RuleTexture.loadFromFile("img/rulebtn.png");
        else RuleTexture.loadTexture2("img/rulebtn.png", 401, 151);
        gSceneTexture.render((gWindow.getWidth() - gSceneTexture.getWidth()) / 2, (gWindow.getHeight() - gSceneTexture.getHeight()) / 2);
        StartTexture.render(gWindow.getWidth() * 11 / 20, gWindow.getHeight() * 3 / 5, NULL, 0, NULL, SDL_FLIP_NONE);
        RuleTexture.render(gWindow.getWidth() * 6 / 20, gWindow.getHeight() * 3 / 5, NULL, 0, NULL, SDL_FLIP_NONE);
        Start.work = 1;
        Rule.work = 1;
        Back.work = 0;
        Back.mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
        break;
    case ruleintro:
        gSceneTexture.free();
        StartTexture.free();
        RuleTexture.free();
        gSceneTexture.loadTexture("img/rulepage.png");
        if (!backon) BackTexture.loadFromFile("img/backbtn.png");
        else BackTexture.loadTexture2("img/backbtn.png", 281, 95);
        gSceneTexture.render((gWindow.getWidth() - gSceneTexture.getWidth()) / 2, (gWindow.getHeight() - gSceneTexture.getHeight()) / 2);
        BackTexture.render(gWindow.getWidth() * 18 / 40, gWindow.getHeight() * 8 / 10);
        Start.work = 0;
        Start.mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
        Rule.work = 0;
        Rule.mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
        Back.work = 1;
        break;
    case choosechar:
        gSceneTexture.free();
        StartTexture.free();
        RuleTexture.free();
        BackTexture.free();
        gSceneTexture.loadTexture("img/choosecharpage.png");
        gSceneTexture.render((gWindow.getWidth() - gSceneTexture.getWidth()) / 2, (gWindow.getHeight() - gSceneTexture.getHeight()) / 2);
        Start.work = 0;
        Start.mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
        Rule.work = 0;
        Rule.mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
        Back.work = 0;
        Back.mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;

        
            if (p1 != 0)
            {
                SDL_Color textColor = { 0, 0, 0 };
                if (!gTextTexture1.loadFromRenderedText("Player1: Yeh (create another gTextTexture and render it) ", textColor))
                {
                    printf("Failed to render text texture!\n");
                }
                gTextTexture1.render((SCREEN_WIDTH - gTextTexture1.getWidth()) / 2, (SCREEN_HEIGHT - gTextTexture1.getHeight()) / 2); //edit this to change location
                if (p2 == 0)
                {
                    p2 = getid.getp1();
                }
            }
            else
            {
                p1 = getid.getp1();
                //try

                ////Clear screen
                //SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                //SDL_RenderClear(gRenderer);

                ////Render current frame
                //gTextTexture1.render((SCREEN_WIDTH - gTextTexture1.getWidth()) / 2, (SCREEN_HEIGHT - gTextTexture1.getHeight()) / 2);

                ////Update screen
                //SDL_RenderPresent(gRenderer);
                //try
            }

            cout << p1 << "," << p2 << endl;


            cout << p1 << "," << p2 << endl;
            if (p1 != 0 && p2 != 0) {
                gamemode = 0;
            }

        
        break;
    case playing:
        gSceneTexture.free();
        gSceneTexture.loadTexture("img/fightpage.png");
        //gTextTexture.render((gWindow.getWidth() - gTextTexture.getWidth()) / 2, (gWindow.getWidth() - gTextTexture.getHeight()) / 2);
        gSceneTexture.render((gWindow.getWidth() - gSceneTexture.getWidth()) / 2, (gWindow.getHeight() - gSceneTexture.getHeight()) / 2);
        break;

        case gameover:
            break;
    }
}





void ingame() {

    Game* game = nullptr;
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    game = new Game(p1, p2);

    game->init("game", 1280, 720, true);

    while (game->running())
    {

        frameStart = SDL_GetTicks();

        game->handleEvents();
        game->update();
        game->render();

        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    game->clean();
    return ;

}







void close()
{

    gTextTexture1.free();
    gTextTexture2.free();
    TTF_CloseFont(gFont);
    gFont = NULL;
    gSceneTexture.free();
    StartTexture.free();
    RuleTexture.free();
    SDL_DestroyRenderer(gRenderer);
    gWindow.free();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* args[]) {
    scenario s = starting;

    if (!init())
    {
        printf("Failed to initialize!\n");
    }
    else
    {
        if (!loadMedia())
        {
            printf("Failed to load media!\n");
        }
        else
        {
            SDL_Event e;
            while (gamemode == 1 && quit == 1) {
                while (SDL_PollEvent(&e) != 0)
                {
                    if (e.type == SDL_QUIT)
                    {
                        quit = 0;
                    }
                    gWindow.handleEvent(e);
                    Start.handleEvent(e);
                    Rule.handleEvent(e);
                    Back.handleEvent(e);
                }
                SDL_RenderClear(gRenderer);
                Start.setPosition(gWindow.getWidth() * 11 / 20, gWindow.getHeight() * 3 / 5);
                Rule.setPosition(gWindow.getWidth() * 6 / 20, gWindow.getHeight() * 3 / 5);
                Back.setPosition(gWindow.getWidth() * 18 / 40, gWindow.getHeight() * 8 / 10);
                //continuously update gRender (may lead to player update questions?)
                putMedia(s);
                SDL_RenderPresent(gRenderer);
                //rule
                if (Rule.mCurrentSprite == BUTTON_SPRITE_MOUSE_UP)
                {
                    s = ruleintro;
                }
                if (Rule.mCurrentSprite == BUTTON_SPRITE_MOUSE_OVER_MOTION)
                {
                    ruleon = true;
                }
                else
                {
                    ruleon = false;
                }
                //start
                if (Start.mCurrentSprite == BUTTON_SPRITE_MOUSE_OVER_MOTION)
                {
                    starton = true;
                }
                else
                {
                    starton = false;
                }
                //back
                if (Back.mCurrentSprite == BUTTON_SPRITE_MOUSE_OVER_MOTION)
                {
                    backon = true;
                }
                else
                {
                    backon = false;
                }
                if (Back.mCurrentSprite == BUTTON_SPRITE_MOUSE_UP)
                {
                    s = starting;
                }
                //press start to choosechar
                if (Start.mCurrentSprite == BUTTON_SPRITE_MOUSE_UP)
                {
                    s = choosechar;
                }
                //Render text

               //SDL_Color textColor = { 0, 0, 0 };
               //if (!gTextTexture.loadFromRenderedText("My time", textColor))
               //{
               //    printf("Failed to render text texture!\n");
               //}
               ////Clear screen
               //SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
               //SDL_RenderClear(gRenderer);

               ////Render current frame
               //gTextTexture.render((SCREEN_WIDTH - gTextTexture.getWidth()) / 2, (SCREEN_HEIGHT - gTextTexture.getHeight()) / 2);

               ////Update screen
               //SDL_RenderPresent(gRenderer);


            }
            while (gamemode == 0 && quit == 1) {
                //need to handle quit again
                //game.getIDfromUser();
                //if (game.success == 0)
                //{
                //    cout << "inside";
                //    s = playing;
                //    //Clear screen
                //    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                //    SDL_RenderClear(gRenderer);
                //    //change page
                //    putMedia(s);
                //    SDL_RenderPresent(gRenderer);
                //    game.success = 1;
                //}
                s = playing;
                SDL_RenderClear(gRenderer);
                
                putMedia(s);
                SDL_RenderPresent(gRenderer);
                close();
                ingame();
                break;
            }
        }
    }
    close();
    return 0;
}






















/*

//Commented Above main functio, Ltexture,Lwindow(all cpp)


#include "SDL.h"
#include "Game.h"

int const SCREEN_WIDTH = 1280;
int const SCREEN_HEIGHT = 720;
Game* game = nullptr;

int main(int argc, char* argv[])
{
	//Limiting Frames
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	game = new Game(1, 4);

	game->init("game",1280, 720, false);

	while (game->running())
	{

		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();
	return 0;

}

*/