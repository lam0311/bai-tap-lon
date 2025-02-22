#include"player.h"
#include"commonFc.h"
#include"map.h"
using namespace std;
void player::box(SDL_Renderer* render, camera cam) {
    SDL_Rect rect = { player_x - cam.camera_x,player_y - cam.camera_y,50,50 };
    SDL_RenderFillRect(render, &rect);
}


void player::aminationrunright(int frame, SDL_Renderer* render, camera cam) {
    SDL_Rect rect = { player_x - cam.camera_x,player_y - cam.camera_y,player_w,player_h };
    SDL_RenderCopy(render, sprite_runright[frame], NULL, &rect);
}

void player::aminationrunleft(int frame, SDL_Renderer* render, camera cam) {
    SDL_Rect rect = { player_x - cam.camera_x,player_y - cam.camera_y,player_w,player_h };
    SDL_RenderCopy(render, sprite_runleft[frame], NULL, &rect);
}



SDL_Texture* player::Loadsprite(const char* path, SDL_Renderer* render) {
    int n = IMG_INIT_PNG;
    if (!(IMG_Init(n) & n)) {
        return NULL;
    }
    SDL_Texture* sprite = NULL;
    SDL_Surface* surface3 = IMG_Load(path);
    if (surface3 == NULL) {
        cout << IMG_GetError();
        return NULL;
    }

    else {
        sprite = SDL_CreateTextureFromSurface(render, surface3);
        picture_w = surface3->w;
        picture_h = surface3->h;
        SDL_FreeSurface(surface3);
        if (!sprite) {
            cout << "khong the tai anh";
            cout << SDL_GetError();
        }
    }
    return sprite;
}





bool player::spriterun(SDL_Renderer* render) {
    char path[50];
    for (int i = 0; i < 17; i++) {
        sprintf_s(path, "picture/walk%d.png", i);
        sprite_runright[i] = Loadsprite(path, render);
        if (sprite_runright[i] == NULL) {
            cout << SDL_GetError();
            return 0;
        }
    }

    char path_[50];
    for (int i = 0; i < 17; i++) {
        sprintf_s(path_, "picture/runleft%d.png", i);
        sprite_runleft[i] = Loadsprite(path_, render);
        if (sprite_runleft[i] == NULL) {
            cout << SDL_GetError();
            return 0;
        }
    }
    return 1;
}










void camera::updateCamera(player x) {

    camera_x = x.player_x - (camera_w / 2);

    camera_y = x.player_y - camera_h / 2;

    if (camera_x < 0) { camera_x = 0; }

    if (camera_y < 0) { camera_y = 0; }

    if (camera_x > MAX_COLS * tile_block - camera_w) {
        camera_x = MAX_COLS * tile_block - camera_w;
    }

    if (camera_y > MAX_ROWS * tile_block - camera_h) {
        camera_y = MAX_ROWS * tile_block - camera_h;
    }
}



void player::checkvar(const int tile_map[MAX_ROWS][MAX_COLS]) {
    int min_h = min(player_h, tile_block);
    int min_w = min(player_w, tile_block);


    int new_x = player_x + x_val;
    int x1 = new_x / tile_block;
    int x2 = (new_x + player_w - 1) / tile_block;
    int y1 = player_y / tile_block;
    int y2 = (player_y + min_h - 1) / tile_block;

    if (x1 >= 0 && x2 < MAX_COLS && y1 >= 0 && y2 < MAX_ROWS) {
        if (x_val > 0) {
            if (tile_map[y1][x2] != 0 || tile_map[y2][x2] != 0) {
                player_x = x2 * tile_block - player_w;
                x_val = 0;
            }
            else {
                player_x += x_val;
            }
        }
        else if (x_val < 0) {
            if (tile_map[y1][x1] != 0 || tile_map[y2][x1] != 0) {
                player_x = (x1 + 1) * tile_block;
                x_val = 0;
            }
            else {
                player_x += x_val;
            }
        }
    }


    int new_y = player_y + y_val;
    x1 = player_x / tile_block;
    x2 = (player_x + min_w - 1) / tile_block;
    y1 = new_y / tile_block;
    y2 = (new_y + player_h - 1) / tile_block;

    if (x1 >= 0 && x2 < MAX_COLS && y1 >= 0 && y2 < MAX_ROWS) {
        if (y_val > 0) {
            if (tile_map[y2][x1] != 0 || tile_map[y2][x2] != 0) {
                player_y = y2 * tile_block - player_h;
                y_val = 0;
                on_ground = true;
            }
            else {
                on_ground = false;
            }
        }
        else if (y_val < 0) {
            if (tile_map[y1][x1] != 0 || tile_map[y1][x2] != 0) {
                player_y = (y1 + 1) * tile_block;
                y_val = 0;
            }
            else {
                player_y += y_val;
                on_ground = false;
            }
        }
    }


    if (player_x < 0) player_x = 0;
    else if (player_x + player_w > MAX_COLS * tile_block) player_x = MAX_COLS * tile_block - player_w;

    if (player_y < 0) player_y = 0;
    else if (player_y + player_h > MAX_ROWS * tile_block) {
        player_y = 0;
        player_x -= 150;
        SDL_Delay(250);
    }
}

void player::jump() {
    if (on_ground) {
        y_val = -9;
        on_ground = false;
    }
}

