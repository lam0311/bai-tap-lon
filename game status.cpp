#include"game status.h"


void status_game::GAME_OVER(SDL_Renderer* render, base game_over) {

    SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
    SDL_RenderClear(render);

    SDL_Delay(200);

    game_over.positionimg(render, NULL);

    /*  SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
      SDL_Rect rect = { 355,450,260,100 };

      SDL_RenderFillRect(render, &rect);*/
    if (mouse_x > 355 && mouse_x < 355 + 260 && mouse_y>450 && mouse_x < 450 + 100) {
        GO = START_AGAIN;
        mouse_x = 0;
        mouse_y = 0;
    }
    SDL_RenderPresent(render);
}