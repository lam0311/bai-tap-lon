#pragma once
#include"commonFc.h"
struct camera;
struct player {
	int player_x;
	int player_y;
	int  player_w;
	int  player_h;
	int x_val;
	float y_val;
	int tileX;
	int tileY;
	bool on_ground;
	int picture_w;
	int picture_h;
	bool attack_corec;
	int player_heath;
	bool player_hit;
	Uint32 player_hit_start;
	int player_frame_hit;
	bool player_died;
	int frame_effect_apple;
	Uint32 time_apple;

	player() {
		player_x = PLAYER_START_X;
		player_y = PLAYER_START_Y;
		player_w = 70;
		player_h = 63;
		picture_w = 0;
		picture_h = 0;
		x_val = 0;
		y_val = 0;
		player_heath = PLAYER_MAX_HEALTH;
		on_ground = false;
		attack_corec = false;
		player_hit = false;
		player_hit_start = 0;
		player_frame_hit = 0;
		player_died = false;
		int frame_effect_apple = 0;
		time_apple = 0;

	}




	void checkvar(const int tile_map[MAX_ROWS][MAX_COLS]);
	void updateTilePosition() {
		tileX = player_x / tile_block;
		tileY = player_y / tile_block;
	}




	void box(SDL_Renderer* render, camera cam);




	SDL_Texture* Loadsprite(const char* path, SDL_Renderer* render);

	bool spriterun(SDL_Renderer* render);
	void aminationrunright(int fame, SDL_Renderer* render, camera cam);
	void aminationrunleft(int fame, SDL_Renderer* render, camera cam);
	void Effect_apple_player(SDL_Renderer* render, camera cam);
	void Effect_apple2_player(SDL_Renderer* render, camera cam);


	void jump();

};

enum playerstate {
	STAND,
	JUMP,
	ATTACK,
	HIT
};


struct camera {
	int camera_x;
	int camera_y;
	int camera_w;
	int camera_h;
	camera() {
		camera_x = 0;
		camera_y = 0;
		camera_w = window_w;
		camera_h = window_h;
	}


	void updateCamera(player x);

	void resetcam();
};



