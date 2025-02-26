#pragma once
#include"commonFc.h"
#include"player.h"
class interface : public player {
public:

	int apple_x;
	int apple_y;

	interface();



	~interface();

	bool blood_index(SDL_Renderer* render);
	void position_blood_index(SDL_Renderer* render, player p1);

	void spamw_apple(SDL_Renderer* render, camera cam);

private:
	SDL_Texture* health;
	SDL_Texture* background_blood;
};