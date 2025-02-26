#include"interface.h"

interface::interface() {
	health = NULL;
	background_blood = NULL;
	apple_x = 18040;
	apple_y = 290;
}
interface::~interface() { ; }


bool interface::blood_index(SDL_Renderer* render) {

	health = Loadsprite("picture/Health.png", render);
	if (health == NULL) {
		return false;
	}

	background_blood = Loadsprite("picture/blood_index.png", render);
	if (background_blood == NULL) {
		return false;
	}


	support_player[0] = Loadsprite("picture/Food.png", render);
	if (!support_player[0]) {
		return false;
	}


	return true;

}

void interface::position_blood_index(SDL_Renderer* render, player p1) {

	SDL_Rect rect1 = { 0,0,28 * p1.player_heath + 24 ,30 };
	SDL_RenderCopy(render, background_blood, NULL, &rect1);

	for (int i = 0; i < p1.player_heath; i++) {
		SDL_Rect rect = { 28 * i + 9,5,24,24 };
		SDL_RenderCopy(render, health, NULL, &rect);
	}

}


void interface::spamw_apple(SDL_Renderer* render, camera cam) {
	SDL_Rect rect = { apple_x - cam.camera_x, apple_y - cam.camera_y, 34, 34 };
	SDL_RenderCopy(render, support_player[0], NULL, &rect);
}