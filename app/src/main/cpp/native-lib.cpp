#include <jni.h>
#include <android/log.h>
#include <cstdlib>
#include <random>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Sprite.h"


#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "SDL_DEMO", __VA_ARGS__))
SDL_Renderer *ren = NULL;
SDL_Joystick *joystick = NULL;
SDL_Surface *surface;
SDL_Surface *bg;
SDL_Texture *texture;
SDL_Texture *bg_texture;


SDL_Rect ball;


bool button_pressed = false;
bool player_flip = false;
Uint32 lastframetime = 0;
int buttonpressis = 99;
int fps = 0;
int frameCount = 0;
Uint32 fpsTimer = 0;
float speed = 300.0f;


int red = 255;
int green;
int blue;


int random_number() {
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 255);
    return dist(gen);
}

void hello() {
    red = random_number();
    green = random_number();
    blue = random_number();
}

void setup() {

//    canvas
    SDL_SetRenderDrawColor(ren, 100, 255, 2, 255);
    SDL_RenderClear(ren);
//    canvas

    //backgroundg
    SDL_RenderCopy(ren, bg_texture, NULL, NULL);
    //backgroundg

    //player
    SDL_RenderCopy(ren, texture, NULL, &ball);
    //player

//    SDL_RenderPresent(ren);

}

void movestick(int stick_type, int stick_value) {
    if (stick_type == 0 and stick_value > 0) {
//        RIGHT
////        LOGI("RIGHT");
        ball.x += 20;

    }

    if (stick_type == 1 and stick_value > 0) {
//        DOWN

        ball.y += 20;
    }

    if (stick_type == 1 and stick_value < 0) {
//        UP MOVEMENT

        ball.y -= 20;
    }


    if (stick_type == 0 and stick_value < 0) {
        //Left movement

        ball.x -= 20;
    }

}

void move(int button_id, float delta, Sprite &player) {

    player.destRect.h = 250;
    player.destRect.w = 250;
//    if(delta>=7.008000){delta=7.008000;}

    if (button_pressed == 1 and button_id == 3) {
        hello();
    }
    if (button_pressed == 1 and button_id == 2) {
        //reset player
        player.destRect.x = 250;
        player.destRect.y = 200;
        player.setFlip(SDL_FLIP_HORIZONTAL);
    }
    if (button_pressed == 1 and button_id == 14) {
//            right movement
//        LOGI("this is %d and button is %d",button_pressed,button_id);
        if (player_flip == true) {
            player_flip = false;
//            LOGI("player is goving  right so we are flipping to right");
            player.setFlip(SDL_FLIP_NONE);
        }
        player.play("walk");

        player.destRect.x += speed * delta;

    }
    if (button_pressed == 1 and button_id == 13) {
//            left movement
//        LOGI("this is %d and button is %d",button_pressed,button_id);
        if (player_flip == false) {

            player_flip = true;
            player.setFlip(SDL_FLIP_HORIZONTAL);
//            LOGI("player is goving  left so we are flipping to left");
        }

        player.play("walk");
        player.destRect.x -= speed * delta;
    }
    if (button_pressed == 1 and button_id == 11) {
//            up movement
//        LOGI("this is %d and button is %d",button_pressed,button_id);
        player.destRect.y -= speed * delta;
    }
    if (button_pressed == 1 and button_id == 12) {
//            down movement
//        LOGI("this is %d and button is %d",button_pressed,button_id);
        player.destRect.y += speed * delta;
    }


    player.update(delta);
}


extern "C" int SDL_main(int argc, char *argv[]) {

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        LOGI("SDL_Init Error: %s", SDL_GetError());
        return 1;
    }

    SDL_Window *win = SDL_CreateWindow("SDL Demo",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       640, 480,
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

    if (SDL_NumJoysticks() < 0) {

        LOGI("JOYSTICK NOT FOUND");
    }
    joystick = SDL_JoystickOpen(0);

    LOGI("joystick FOUND : %s", SDL_JoystickName(joystick));
    LOGI("joystick connected : %d", SDL_JoystickInstanceID(joystick));


    // Main loop (render red screen)
    bool running = true;
    SDL_Event e;


    ball.y = 200;
    ball.x = 250;
    ball.w = 500;
    ball.h = 500;

//    surface= SDL_LoadBMP("player/mario.bmp");

//    surface= IMG_Load("player/sprites/luigi.png");
//    SDL_Texture* playerTex = IMG_LoadTexture(ren, "player/sprites/luigi.png");

    IMG_Init(IMG_INIT_PNG);


    bg = SDL_LoadBMP("background/background2.bmp");

    // Load texture
    SDL_Texture *playerTexture = IMG_LoadTexture(ren, "player/sprites/new_lugi.png");

    // Create Sprite object
    Sprite player(playerTexture, 100, 100, 64, 64);



    // x=100, y=100, frame width=64, height=64

    player.addAnimation("idle", 1, 4, 2.1f); // row 0, 4 frames, 0.1s per frame
    player.addAnimation("walk", 0, 3, 0.23); // row 0, 4 frames, 0.1s per frame

    player.play("idle");


    if (!playerTexture) {
        LOGI("Failed to load playerr texture : %s", SDL_GetError());
        return 1;
    }

    if (!bg) {
        LOGI("Failed to load BMP BG : %s", SDL_GetError());
        return 1;
    }


//   / texture= IMG_LoadTexture(ren, "player/sprites/luigi.png");;

    bg_texture = SDL_CreateTextureFromSurface(ren, bg);

//    if(!texture || !bg_texture){
//        LOGI("Failed to load Texture: %s", SDL_GetError());
//        return 1;
//    }

    SDL_FreeSurface(surface);
    SDL_FreeSurface(bg);


    lastframetime = SDL_GetTicks();
    fpsTimer = SDL_GetTicks();
    while (running) {
//        LOGI("%d",player_flip);
//        delta
        Uint32 now = SDL_GetTicks();
        float delta = (now - lastframetime) / 1000.0f;
        lastframetime = now;

//        delta = SDL_clamp(delta, 0.0f, 0.05f);
//        delta

//fps
        frameCount++;

        if (SDL_GetTicks() - fpsTimer >= 1000) {
            LOGI("FPS: %d \nDELTA : %f", frameCount, delta);
            frameCount = 0;
            fpsTimer = SDL_GetTicks();
        }
//fps

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;

//            if (e.type == SDL_JOYAXISMOTION) {
//                LOGI("JOYSTICK %d moving %d", e.jaxis.axis, e.jaxis.value);
//                movestick(e.jaxis.axis, e.jaxis.value);
//            }

            if (e.type == SDL_JOYBUTTONUP) {
                button_pressed = false;
//                LOGI("JOYSTICK Button up %d ", e.jbutton.button);


            }
            if (e.type == SDL_JOYBUTTONDOWN) {

                button_pressed = true;
//                LOGI("button_pressed %d", e.jbutton.button);
//                      move_button(e.jbutton.button);
                buttonpressis = e.jbutton.button;
//                )
            }




//            if (e.type == SDL_FINGERDOWN){
//                hello();
//            };
        }
//        SDL_RenderFillRect(ren, &rectangel);

        move(buttonpressis, delta, player);
        setup();

        if(button_pressed== false){
            player.play("idle");
        }

//        LOGI("%d",button_pressed);
        player.update(delta);  // animation update
        player.render(ren);   // draw on screen
        SDL_RenderPresent(ren);

    }

    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(bg_texture);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
