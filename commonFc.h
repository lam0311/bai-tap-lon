#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
#include"math.h"
using namespace std;

static SDL_Window* window = NULL;
static SDL_Renderer* render = NULL;
static SDL_Event e;



static SDL_Texture* style_map[10];
static SDL_Texture* sprite_runright[16];
static SDL_Texture* sprite_runleft[16];
static SDL_Texture* sprite_attackright[10];
static SDL_Texture* sprite_attackleft[10];
static SDL_Texture* sprite_hit_right[4];
static SDL_Texture* sprite_hit_left[4];



// goblin
static SDL_Texture* sprite_goblin_idle = NULL;
static SDL_Texture* sprite_goblin_runright[9];
static SDL_Texture* sprite_goblin_runleft[9];
static SDL_Texture* sprite_goblin_attackright[7];
static SDL_Texture* sprite_goblin_attackleft[7];
static SDL_Texture* sprite_goblin_hit_right[4];
static SDL_Texture* sprite_goblin_hit_left[4];


// bien hang
const int window_w = 1280;
const int window_h = 640;
const int BBF = 32;
const int KEY_R = 167;
const int KEY_G = 175;
const int KEY_B = 180;
const int tile_block = 64;
const int MAX_ROWS = 12;
const int MAX_COLS = 400;
