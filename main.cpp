#define SDL_MAIN_HANDLED
#include"commonFc.h"
#include"base oj.h"
#include"map.h"
#include"player.h"
#include"attack.h"
#include"enemy.h"
#include"interface.h"
#include"game status.h"

player p1;
camera cam;
attack at;
vector<enemy> enemy_g(100);
interface inter;
status_game status;


map mp;
base background;
base game_over_;
// shift+alt+.

bool setup() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << SDL_GetError();
        return false;
    }
    window = SDL_CreateWindow("natra", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_w, window_h, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        cout << SDL_GetError();
        return false;
    }
    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (render == NULL) {
        cout << SDL_GetError();
        return false;
    }
    SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
    return true;
}



void close() {
    background.free();
    for (int i = 0; i < 10; i++) {
        SDL_DestroyTexture(style_map[i]);
    }
    for (int i = 0; i < 17; i++) {
        SDL_DestroyTexture(sprite_runright[i]);
    }
    for (int i = 0; i < 17; i++) {
        SDL_DestroyTexture(sprite_runleft[i]);
    }
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}




bool setbackground() {
    bool back = background.loadimg("picture/Pixel Art forest #2.jpg", render, 1280, 640);
    bool over = game_over_.loadimg("picture/retry.png", render, 1280, 640);
    return back || over;
}

bool stylemap() {
    mp.readfile();
    bool st = mp.loadTile(render, "picture/map1.png", 1);
    bool st1 = mp.loadTile(render, "picture/map2.png", 2);
    bool st2 = mp.loadTile(render, "picture/cua.png", 3);
    return st || st1 || st2;
}




void move_(int framerun, camera cam, SDL_Renderer* render, player& p1, bool left, bool right, bool direcleft, bool direcright, bool isattack, attack at, int framattack) {
    if (right) {
        if (p1.on_ground) {
            p1.aminationrunright(framerun, render, cam);
        }
        else {
            p1.aminationrunright(10, render, cam);
        }
    }

    else if (left) {
        if (p1.on_ground) {
            p1.aminationrunleft(framerun, render, cam);
        }
        else {
            p1.aminationrunleft(10, render, cam);
        }
    }

    else if (isattack) {
        if (direcright) {
            at.aminationattackright(framattack, render, cam, p1);
        }
        else if (direcleft) {
            at.aminationattackleft(framattack, render, cam, p1);
        }
    }

    else if (p1.player_hit) {
        if (direcright) {
            at.amination_hit_right(p1.player_frame_hit, render, cam, p1);
        }
        else if (direcleft) {
            at.amination_hit_left(p1.player_frame_hit, render, cam, p1);
        }
    }

    else {
        if (direcright) {
            p1.aminationrunright(0, render, cam);
        }
        else if (direcleft) {
            p1.aminationrunleft(0, render, cam);
        }
        else {
            p1.aminationrunright(0, render, cam);
        }
    }
}




void resetgame() {

    p1.player_x = PLAYER_START_X;
    p1.player_y = PLAYER_START_Y;
    p1.player_heath = PLAYER_MAX_HEALTH;
    p1.x_val = 0;
    p1.y_val = 0;
    p1.player_died = false;
    p1.player_hit = false;
    p1.player_frame_hit = 0;

    for (int i = 0; i < 37; i++) {
        enemy_g[i].enemy_x = 600 + 700 * i;
        enemy_g[i].enemy_y = 40;
        enemy_g[i].goblin_heath = 3;
        enemy_g[i].goblin_dead = false;
        enemy_g[i].kt_died_goblin = false;
        enemy_g[i].goblin_hit = false;
        enemy_g[i].frame_died_goblin = 0;
    }
    cam.resetcam();
}




int main(int argc, char* argv[]) {
    const int(&mapArray)[MAX_ROWS][MAX_COLS] = mp.getmap();



    playerstate p1state = STAND;
    state_goblin goblin = STANDUP;


    // thời gian chạy frame tấn công 
    bool isAttack = false;
    Uint32 attackStart = 0;
    const Uint32 attacktime = 200;
    int frameattack = 1;
    int frame_hit = 0;
    Uint32 time_hit = 0;



    enemy enemy;

    // spamw vị trí của goblin 
    for (int i = 0; i < 37; i++) {
        enemy_g[i].enemy_x = 600 + 700 * i;
        enemy_g[i].enemy_y = 40;
    }
    // biến tấn công của goblin
    Uint32 attack_goblin_time = 500;
    int frame_attack_goblin = 0;
    bool goblin_hit_yes = false;



    const int vantoc = 4;
    const int vector_y = 1;

    bool right = false, left = false;
    bool checkjump = false;
    bool direcright = false, direcleft = false;
    bool hit = false;


    // thời gian chạy frame di chuyển
    int frame_goblin_run = 0;
    Uint32 time_goblin_run = 0;
    int framerun = 0;
    Uint32 timerun = 0;

    if (!setup() || !setbackground() || !stylemap() || !p1.spriterun(render) || !at.loadattack(render) || !enemy.amination_enemy_goblin(render)
        || !inter.blood_index(render)) {
        cout << SDL_GetError();
        return 1;
    }

    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
                break;
            }
            else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                case SDLK_RIGHT:
                    right = true;
                    left = false;
                    p1.x_val = vantoc;
                    direcright = true;
                    direcleft = false;
                    break;
                case SDLK_LEFT:
                    left = true;
                    right = false;
                    p1.x_val = -vantoc;
                    direcright = false;
                    direcleft = true;
                    break;
                case SDLK_UP:
                    p1.jump();

                    break;
                }
            }



            else if (e.type == SDL_MOUSEBUTTONDOWN) {
                Uint32 delay_attack = SDL_GetTicks();
                if (e.button.button == SDL_BUTTON_LEFT && !right && !left && delay_attack - attackStart >= 400) {
                    isAttack = true;
                    attackStart = SDL_GetTicks();
                    goblin_hit_yes = true;
                }

                int m;
                int n;
                SDL_GetMouseState(&m, &n);

                status.mouse_x = m;
                status.mouse_y = n;


            }





            else if (e.type == SDL_KEYUP) {
                switch (e.key.keysym.sym) {
                case SDLK_RIGHT:
                    right = false;
                    if (!right) p1.x_val = 0;
                    break;
                case SDLK_LEFT:
                    left = false;
                    if (!left) p1.x_val = 0;
                    break;
                }

                if (!left && !right) {
                    p1state = STAND;
                }
            }

        }


        if (!p1.on_ground) {
            p1.y_val += 0.5;
            if (p1.y_val > 7) {
                p1.y_val = 7;
            }
        }
        else {
            p1.y_val = 1;
        }


        // nhan vat dieu khien
        p1.checkvar(mapArray);
        p1.player_x += p1.x_val;
        p1.player_y += p1.y_val;
        cam.updateCamera(p1);

        SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
        SDL_RenderClear(render);





        if (p1.player_heath <= 0) {
            status.GAME_OVER(render, game_over_);
            if (status.GO == START_AGAIN) {
                resetgame();
                status.GO = START;
            }

        }
        else {
            background.positionimg(render, NULL);
            mp.rendermap(render, cam);

            Uint32 goblin_frame_hit = 0;

            p1.Effect_apple_player(render, cam);
            p1.Effect_apple2_player(render, cam);
            move_(framerun, cam, render, p1, left, right, direcleft, direcright, isAttack, at, frameattack);


            for (int i = 0; i < 37; i++) {

                if (enemy_g[i].goblin_dead) {
                    if (!enemy_g[i].kt_died_goblin) {
                        if (enemy_g[i].direc_goblin_left) {
                            enemy_g[i].sprite_enemy_goblin_died_right(enemy_g[i].frame_died_goblin, render, cam);
                        }
                        else {
                            enemy_g[i].sprite_enemy_goblin_died_left(enemy_g[i].frame_died_goblin, render, cam);
                        }

                        Uint32 currentime = SDL_GetTicks();
                        if (currentime - enemy_g[i].goblin_frame_died > 130) {
                            if (enemy_g[i].frame_died_goblin < 3) {
                                enemy_g[i].frame_died_goblin++;
                                enemy_g[i].goblin_frame_died = SDL_GetTicks();
                            }
                            else {
                                enemy_g[i].kt_died_goblin = true;
                            }
                        }
                    }
                    else {

                        if (enemy_g[i].direc_goblin_left) {
                            enemy_g[i].sprite_enemy_goblin_died_right(3, render, cam);
                        }
                        else {
                            enemy_g[i].sprite_enemy_goblin_died_left(3, render, cam);
                        }
                    }

                    continue;
                }




                if (isAttack && direcright && enemy_g[i].enemy_x - p1.player_x < 80 && enemy_g[i].enemy_x - p1.player_x > 0 && abs(enemy_g[i].enemy_y - p1.player_y) < 40) {
                    if (direcright) {
                        enemy_g[i].goblin_hit = true;
                        enemy_g[i].goblin_hit_start = SDL_GetTicks();
                        if (goblin_hit_yes) {
                            enemy_g[i].goblin_heath -= 1;
                            goblin_hit_yes = false;
                        }

                    }
                }

                else if (isAttack && direcleft && enemy_g[i].enemy_x - p1.player_x > -80 && enemy_g[i].enemy_x - p1.player_x < 0 && abs(enemy_g[i].enemy_y - p1.player_y) < 40) {
                    if (direcleft) {
                        enemy_g[i].goblin_hit = true;
                        enemy_g[i].goblin_hit_start = SDL_GetTicks();
                        if (goblin_hit_yes) {
                            enemy_g[i].goblin_heath -= 1;
                            goblin_hit_yes = false;
                        }

                    }
                }
                enemy_g[i].enemy_goblin_health(render, cam);


                if (enemy_g[i].goblin_hit) {

                    if (enemy_g[i].direc_goblin_left) {
                        enemy_g[i].sprite_enemy_goblin_hurt_left(frame_hit, render, cam);
                    }
                    else {
                        enemy_g[i].sprite_enemy_goblin_hurt_right(frame_hit, render, cam);
                    }

                    Uint32 currentime = SDL_GetTicks();
                    if (currentime - goblin_frame_hit > 80) {
                        frame_hit = (frame_hit + 1) % 4;
                        goblin_frame_hit = SDL_GetTicks();
                    }
                    if (currentime - enemy_g[i].goblin_hit_start >= 200) {

                        if (enemy_g[i].goblin_heath <= 0) {
                            enemy_g[i].goblin_dead = true;
                            enemy_g[i].goblin_frame_died = SDL_GetTicks();
                            enemy_g[i].frame_died_goblin = 0;
                        }
                        else {
                            enemy_g[i].goblin_hit = false;
                            frame_hit = 0;
                        }
                    }

                }



                enemy_g[i].followPlayer(p1, mapArray, goblin, frame_goblin_run, render, cam);
                enemy_g[i].update(mapArray);
                if (!enemy_g[i].goblin_hit) {
                    if (goblin == STANDUP) {
                        enemy_g[i].spam_enemy_goblin(render, cam);
                    }
                    else if (goblin == RUNLEFT) {
                        enemy_g[i].sprite_enemy_goblin_left(frame_goblin_run, render, cam);
                    }
                    else if (goblin == RUNRIGHT) {
                        enemy_g[i].sprite_enemy_goblin_right(frame_goblin_run, render, cam);
                    }
                    else if (goblin == ATTACK_GOBLIN) {
                        if (enemy_g[i].direc_goblin_left) {
                            enemy_g[i].sprite_enemy_goblin_attack_left(frame_attack_goblin, render, cam);
                        }
                        else if (enemy_g[i].direc_goblin_right) {
                            enemy_g[i].sprite_enemy_goblin_attack_right(frame_attack_goblin, render, cam);
                        }
                    }


                    if (goblin == RUNLEFT || goblin == RUNRIGHT) {
                        Uint32 currentTime_ = SDL_GetTicks();
                        if (currentTime_ - time_goblin_run > 80) {
                            frame_goblin_run = (frame_goblin_run + 1) % 8;
                            time_goblin_run = SDL_GetTicks();
                        }
                    }


                    if (enemy_g[i].isattack_goblin) {
                        Uint32 currentTime = SDL_GetTicks();
                        if (currentTime - time_goblin_run > 120) {
                            frame_attack_goblin = (frame_attack_goblin + 1) % 6;
                            time_goblin_run = SDL_GetTicks();
                        }
                        if (currentTime - enemy_g[i].attack_goblin_start >= attack_goblin_time) {
                            enemy_g[i].isattack_goblin = false;
                            frame_attack_goblin = 0;
                        }
                        if (abs(enemy_g[i].enemy_x - p1.player_x) < 75 && abs(enemy_g[i].enemy_y - p1.player_y) < 40) {
                            if (!enemy_g[i].prep_attack) {
                                enemy_g[i].prep_attack = true;
                                enemy_g[i].attack_goblin_start = SDL_GetTicks();
                            }

                            else {
                                Uint32 currentTime1 = SDL_GetTicks();
                                if (currentTime1 - enemy_g[i].attack_goblin_start >= 370) {
                                    if (enemy_g[i].enemy_x - p1.player_x < 75 && enemy_g[i].enemy_x - p1.player_x >0 && enemy_g[i].direc_goblin_left && abs(enemy_g[i].enemy_y - p1.player_y) < 40) {

                                        if (!p1.player_hit) {
                                            p1.player_hit = true;
                                            p1.player_hit_start = SDL_GetTicks();
                                            p1.player_frame_hit = 0;
                                            p1.player_heath--;
                                        }
                                    }
                                    else if (enemy_g[i].enemy_x - p1.player_x > -75 && enemy_g[i].enemy_x - p1.player_x < 0 && enemy_g[i].direc_goblin_right && abs(enemy_g[i].enemy_y - p1.player_y) < 40) {
                                        if (!p1.player_hit) {
                                            p1.player_hit = true;
                                            p1.player_hit_start = SDL_GetTicks();
                                            p1.player_frame_hit = 0;
                                            p1.player_heath--;
                                        }
                                    }
                                    enemy_g[i].prep_attack = false;
                                }
                            }
                        }
                        else {
                            enemy_g[i].prep_attack = false;

                        }
                    }
                }
            }


            inter.spamw_apple(render, cam);
            inter.position_blood_index(render, p1);


            SDL_RenderPresent(render);




            if (right || left) {
                if (SDL_GetTicks() - timerun > 40) {
                    framerun = (framerun + 1) % 16;
                    if (framerun == 0) {
                        framerun = 1;
                    }
                    timerun = SDL_GetTicks();
                }
            }



            else if (isAttack) {
                Uint32 currentTime = SDL_GetTicks();
                if (currentTime - timerun > 100) {
                    frameattack = (frameattack + 1) % 4;
                    if (frameattack == 0) {
                        frameattack = 1;
                    }
                    timerun = SDL_GetTicks();

                }
                if (currentTime - attackStart >= attacktime) {
                    isAttack = false;
                }
            }
            else if (p1.player_hit) {
                Uint32 currentTime = SDL_GetTicks();
                if (currentTime - timerun > 200) {
                    p1.player_frame_hit++;
                    timerun = SDL_GetTicks();
                }

                if (p1.player_frame_hit >= 4) {
                    p1.player_hit = false;
                    p1.player_frame_hit = 0;
                }
            }
            else {
                framerun = 0;
            }




            SDL_Delay(16);
        }
    }

    close();
    return 0;
}
