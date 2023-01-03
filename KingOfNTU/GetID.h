#pragma once

#include <SDL.h>
#include <iostream>
using namespace std;
//extern bool *getidsuccess;


class GetID {
public:

    int getp1() {
        //cout << "1" << endl;
        SDL_Event event;
        SDL_PollEvent(&event);
        if (event.type == SDL_KEYDOWN)
        {
            //cout << "1" << endl;
            if (event.key.keysym.sym == SDLK_1) return 1;
            if (event.key.keysym.sym == SDLK_2) return 2;
            if (event.key.keysym.sym == SDLK_3) return 3;
            if (event.key.keysym.sym == SDLK_4) return 4;
            if (event.key.keysym.sym == SDLK_5) return 5;
            if (event.key.keysym.sym == SDLK_6) return 6;

        }
        return 0;
    }
};