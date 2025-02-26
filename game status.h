#pragma once
#include"commonFc.h"
#include"base oj.h"
enum GAME {
    START,
    MENU,
    HELP,
    START_AGAIN
};
class status_game {
public:
    int mouse_x;
    int mouse_y;
    GAME GO;
    status_game() {
        mouse_x = 0;
        mouse_y = 0;
        GO = START;
    }
    void GAME_OVER(SDL_Renderer* render, base game_over);
};