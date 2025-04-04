#pragma once
#include"commonFc.h"
#include"player.h"

enum state_goblin {
	STANDUP,
	RUNLEFT,
	RUNRIGHT,
	ATTACK_GOBLIN
};
class enemy :public player {
public:
	int enemy_x;
	int enemy_y;
	int enemy_w;
	int enemy_h;
	int enemy_x_val;
	float enemy_y_val;
	bool enemy_on_ground;
	bool direc_goblin_right;
	bool direc_goblin_left;
	bool isattack_goblin;
	int goblin_heath;
	bool goblin_dead;
	bool goblin_hit;
	Uint32 goblin_hit_start;
	Uint32 goblin_frame_died;
	bool kt_died_goblin;
	int frame_died_goblin;
	bool prep_attack;


	Uint32 attack_goblin_start;
	SDL_Texture* load_enemy(const char* path, SDL_Renderer* render);

	vector<pair<int, int>> picture_attack_left;


	enemy();



	void checkvar2(const int tile_map[MAX_ROWS][MAX_COLS]);
	void update(const int tile_map[MAX_ROWS][MAX_COLS]);


	void followPlayer(player p1, const int tile_map[MAX_ROWS][MAX_COLS], state_goblin& goblin, int frame, SDL_Renderer* render, camera cam);
	bool amination_enemy_goblin(SDL_Renderer* render);
	void spam_enemy_goblin(SDL_Renderer* render, camera& cam);
	void sprite_enemy_goblin_left(int frame, SDL_Renderer* render, camera& cam);
	void sprite_enemy_goblin_right(int frame, SDL_Renderer* render, camera& cam);
	void sprite_enemy_goblin_attack_right(int frame, SDL_Renderer* render, camera& cam);
	void sprite_enemy_goblin_attack_left(int frame, SDL_Renderer* render, camera& cam);
	void sprite_enemy_goblin_hurt_left(int frame, SDL_Renderer* render, camera& cam);
	void sprite_enemy_goblin_hurt_right(int frame, SDL_Renderer* render, camera& cam);
	void sprite_enemy_goblin_died_right(int frame, SDL_Renderer* render, camera& cam);
	void sprite_enemy_goblin_died_left(int frame, SDL_Renderer* render, camera& cam);
	void enemy_goblin_health(SDL_Renderer* render, camera& cam);



};