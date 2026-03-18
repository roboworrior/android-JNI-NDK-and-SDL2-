#include <jni.h>
#include <android/log.h>
#include <cstdlib>
#include <random>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <SDL_ttf.h>

#include "globals.h"
#include "Sprite.h"
#include "controler.h"

#include "setup.h"
#include "render.h"
#include "move.h"



void cleanup()
{
    SDL_DestroyTexture(bg_texture);
    SDL_DestroyTexture(dpad_texture);
    SDL_DestroyTexture(textTexture);



    SDL_FreeSurface(textSurface);
    SDL_FreeSurface(bg);


    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

int random_number() {
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 255);
    return dist(gen);
}

void hello() {

}



void fps_counter(float delta) {
    frameCount++;

    if (SDL_GetTicks() - fpsTimer >= 1000) {
//        LOGI("FPS: %d \nDELTA : %f", frameCount, delta);
        fps = frameCount;
        frameCount = 0;
        fpsTimer = SDL_GetTicks();

    }

}


float delta_fun() {

    Uint32 now = SDL_GetTicks();
    float delta = (now - lastframetime) / 1000.0f;
    lastframetime = now;
    delta = SDL_clamp(delta, 0.0f, 0.05f);
    return delta;
}






void inair(Sprite &player,float  &delta){
//    LOGI(" on air is : %d",player_onair);

player_onair= true;
for(int i=0;i<total_bricks;i++) {


    if (SDL_HasIntersection(&player_hitbox, &brick_dstrect_colustion[i])) {

        player_onair = false;

        break;
    }

}

    if(player.destRect.y == wall_down.y-player.destRect.h  ){

        //this will turn off the on air when player reched to ground
        player_onair= false;

        }

    if(player_onair){

//        player_onair= false;
        move(12,delta,player);
    }



}



extern "C" int SDL_main(int argc, char *argv[]) {

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) != 0) {
        LOGI("SDL_Init Error: %s", SDL_GetError());
        return 1;
    }

    win = SDL_CreateWindow("SDL Demo",
                           SDL_WINDOWPOS_CENTERED,
                           SDL_WINDOWPOS_CENTERED,
                           1280, 720,
                           SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);

    if (!win) {
        LOGI("SDL_CreateWindow Error: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    if (!ren) {
        SDL_DestroyWindow(win);
        LOGI("SDL_CreateRenderer Error: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }



    bool running = true;
    SDL_Event e;

    IMG_Init(IMG_INIT_PNG);
     TTF_Init();
     font_small = TTF_OpenFont("fonts/Noto_Sans/static/NotoSans-Bold.ttf", 50);
     font_big = TTF_OpenFont("fonts/Noto_Sans/static/NotoSans-Bold.ttf", 70);


    if(!font_small||!font_big){
        LOGI("font not found");
        return 1;
    }




    // Load texture
    bg = SDL_LoadBMP("background/background2.bmp");
    playerTexture = IMG_LoadTexture(ren, "player/sprites/new_lugi.png");
    enemie1Texture = IMG_LoadTexture(ren, "ememies/green duck.png");

    dpad_texture = IMG_LoadTexture(ren, "on screen control/dpad1.png");
    itemTexture = IMG_LoadTexture(ren, "items/Untitled.png");

    bg_texture = SDL_CreateTextureFromSurface(ren, bg);


    if (!playerTexture || !enemie1Texture) {
        LOGI("Failed to load playerr texture : %s", SDL_GetError());
        return 1;
    }

    if (!bg) {
        LOGI("Failed to load BMP BG : %s", SDL_GetError());
    }
    if(!dpad_texture){
        LOGI("Failed to dpad texture : %s", SDL_GetError());
        return 1;

    }

    // Create Sprite object
    Sprite player(playerTexture, 0, 0, 64, 64);

    player.addAnimation("walk", 0, 3,0.2f); // row 0, 4 frames, 0.1s per frame ( less speed value=== fash animetion play like 0.1f)
    player.addAnimation("idle", 1, 4, 2.1f); // row 0, 4 frames, 0.1s per frame
    player.addAnimation("jump", 2, 3,0.2f); // row 0, 4 frames, 0.1s per frame ( less speed value=== fash animetion play like 0.1f)


    Sprite enemie1(enemie1Texture, 0, 0, 64, 64);
    enemie1.addAnimation("walk", 0, 3,0.2f); // row 0, 4 frames, 0.1s per frame ( less speed value=== fash animetion play like 0.1f)

    SDL_FreeSurface(bg);

    lastframetime = SDL_GetTicks();
    fpsTimer = SDL_GetTicks();

    setup(player,enemie1);


    //main game loop
    while (running) {

        float delta = delta_fun();
         fps_counter(delta);
//        LOGI("fps : %d", fps_counter(delta));

        inair(player,delta);


        //loop for events
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;

            if (e.type == SDL_FINGERDOWN)
            {
                isMoving = false;
                float x = e.tfinger.x*screen_width ;
                float y = e.tfinger.y*screen_height ;

                SDL_Point p = {(int) x,(int) y};   // 👉 YEH YAHAN AYEGA
//                    LOGI("x : %f, y : %f", x, y);

                if (SDL_PointInRect(&p, &dpad_right))
                {
//                    LOGI("it the onscreen control ");
                    onscreen_control="right";
                }
                if (SDL_PointInRect(&p, &dpad_left))
                {
//                    LOGI("it the onscreen control ");
                    onscreen_control="left";
                }
                if (SDL_PointInRect(&p, &dpad_down))
                {
//                    LOGI("it the onscreen control ");
                    onscreen_control="down";
                }
                if (SDL_PointInRect(&p, &dpad_up))
                {
//                    LOGI("it the onscreen control ");
                    onscreen_control="up";
                }
                if (SDL_PointInRect(&p, &dpad_a))
                {
                    LOGI("it the onscreen control button a ");
                    onscreen_control="btn_a";
                }
                if (SDL_PointInRect(&p, &dpad_b))
                {
                    LOGI("it the onscreen control button b");
                    onscreen_control="btn_b";

                }
                if (SDL_PointInRect(&p, &dpad_close_input))
                {
                    cleanup();

                }
                if (SDL_PointInRect(&p, &dpad_close_start))
                {
                    LOGI("it the onscreen control button start");
                    onscreen_control="btn_start";

                }


            }


            if (e.type == SDL_FINGERUP)
            {
//                LOGI("fingerUP");
                    onscreen_control="none";
            }

            if(e.type== SDL_CONTROLLERBUTTONUP){
                onscreen_control="none";
            }

            if (e.type == SDL_CONTROLLERDEVICEADDED){

                connectController(e.cdevice.which);
            }

            if (e.type == SDL_CONTROLLERDEVICEREMOVED){

                disconnectController(e.cdevice.which);
                }


        }


        if (controller) {
            if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_UP)) {
                onscreen_control="up";
//                    LOGI("%d",SDL_CONTROLLER_BUTTON_DPAD_RIGHT);

            }
            if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_DOWN)) {
                onscreen_control="down";
            }
            if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT)) {
                onscreen_control="left";
            }
            if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT)) {
                onscreen_control="right";
                //                    LOGI("%d",SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
            }
            if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A)) {
                onscreen_control="btn_a";
            }
            if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_B)) {
                onscreen_control="btn_b";
            }
            if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_Y)) {
                onscreen_control="btn_y";
            }
            if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_BACK)) {
                    cleanup();
//                LOGI("this is select");
            }
            if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_START)) {
                onscreen_control="btn_start";
//                LOGI("this is select");
            }


        }


        render(player,enemie1,delta);
        player.update(delta);  // animation update

        if(!enemie_dead){
//            enemie_dead= true;
            enemie1.update(delta);  // animation update
        }


//        enemie1.update(delta);  // animation update

        if(onscreen_control == "none") {
                isMoving= false;
        }
        if(onscreen_control == "left"){

            isMoving= true;
            move(SDL_CONTROLLER_BUTTON_DPAD_LEFT,delta,player);
//            player.play("walk");
            }
        if(onscreen_control == "right"){

            isMoving= true;
//            player.play("walk");
            move(SDL_CONTROLLER_BUTTON_DPAD_RIGHT,delta,player);
        }
        if(onscreen_control == "up"){

            isMoving= true;
            move(SDL_CONTROLLER_BUTTON_DPAD_UP,delta,player);
        }
        if(onscreen_control == "down"){

            isMoving= true;
            move(SDL_CONTROLLER_BUTTON_DPAD_DOWN,delta,player);
        }
        if(onscreen_control == "btn_a"){

            isMoving= true;
            move(SDL_CONTROLLER_BUTTON_A,delta,player);
        }
        if(onscreen_control == "btn_b"){

            isMoving= true;
            move(SDL_CONTROLLER_BUTTON_B,delta,player);
        }
        if(onscreen_control == "btn_y"){

            isMoving= true;
            move(SDL_CONTROLLER_BUTTON_Y,delta,player);
        }
        if(onscreen_control == "btn_start"){

            isMoving= true;
            p1_stats.player_win= false;
            move(SDL_CONTROLLER_BUTTON_START,delta,player);
        }

        if(onscreen_control == "btn_close"){

            isMoving= true;
            LOGI("this is close");
//            move(SDL_CONTROLLER_BUTTON_Y,delta,player);
        }


        if (isMoving == false) {
            player.play("idle");

        }


        enem_move(enemie1,brick_dstrect[1],delta,player);

        if( p1_stats.powerup_fired== true){
//        p1_stats.powerup_status= false;

            powerup1_dstrect.x-=speed*delta;

        }


        if(SDL_HasIntersection(&powerup1_dstrect,&enemie1.destRect) && p1_stats.powerup_fired== true){
            enemie_dead= true;

            LOGI("this sis deuck dead");
        }
//            LOGI("totla conis :%d",p1_stats.coins);



        if(p1_stats.coins==items.size()-1 && enemie_dead== true ){

            SDL_Delay(1000);
            p1_stats.player_win= true;

        }

//        timer=SDL_GetTicks();
//        LOGI("this is ticks :%d",timer);


    }


    cleanup();
    return 0;
}
