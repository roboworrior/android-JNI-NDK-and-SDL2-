#include <jni.h>
#include <android/log.h>
#include <cstdlib>
#include <random>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>

#include "Sprite.h"


#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "SDL_DEMO", __VA_ARGS__))
SDL_Renderer *ren = NULL;
SDL_Window *win = NULL;
SDL_Joystick *joystick = NULL;
SDL_GameController *controller = NULL;
SDL_Surface *surface;
SDL_Surface *bg;
SDL_Texture *texture;
SDL_Texture *bg_texture;

bool button_pressed = false;
bool vsync = false;
bool player_flip = false;
Uint32 lastframetime = 0;
bool isMoving = false;   // har frame reset karo
int fps = 0;
int frameCount = 0;
Uint32 fpsTimer = 0;
float speed = 450.0f;


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

//controler login
void connectController(int index) {

    if (!SDL_IsGameController(index)) return;

    controller = SDL_GameControllerOpen(index);

    if (controller) {
        LOGI("Controller Connected: %s",
             SDL_GameControllerName(controller));
    }
}


void disconnectController(SDL_JoystickID id) {

    if (!controller) return;

    SDL_Joystick *joy =
            SDL_GameControllerGetJoystick(controller);

    if (SDL_JoystickInstanceID(joy) == id) {

        SDL_GameControllerClose(controller);
        controller = NULL;

        LOGI("Controller Removed");
    }
}

//controler login


void fps_counter(float delta) {
    frameCount++;

    if (SDL_GetTicks() - fpsTimer >= 1000) {
        LOGI("FPS: %d \nDELTA : %f", frameCount, delta);

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

void setup(Sprite player, float delta) {


    player.destRect.h = 250;
    player.destRect.w = 250;

//    canvas
    SDL_SetRenderDrawColor(ren, 100, 255, 2, 255);
    SDL_RenderClear(ren);
//    canvas

    //backgroundg
    SDL_RenderCopy(ren, bg_texture, NULL, NULL);
    //backgroundg


    player.update(delta);  // animation update

    player.render(ren);   // draw on screen

    SDL_RenderPresent(ren);

}

void movestick(int stick_type, int stick_value) {
    if (stick_type == 0 and stick_value > 0) {
//        RIGHT
////        LOGI("RIGHT");


    }

    if (stick_type == 1 and stick_value > 0) {
//        DOWN


    }

    if (stick_type == 1 and stick_value < 0) {
//        UP MOVEMENT


    }


    if (stick_type == 0 and stick_value < 0) {
        //Left movement


    }

}

void move(int button_id, float delta, Sprite &player) {

//    if(delta>=7.008000){delta=7.008000;}

    if (button_id == 3) {
        hello();
    }

    if (button_id == 734) {

        if (vsync == false) {
            vsync = true;
            LOGI("vsyn on");
            ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        }
        if (vsync == true) {
            vsync = false;
            LOGI("vsyn off");
            ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
        }

    }

    if (button_id == 0) {
        //reset player
        player.destRect.x = 250;
        player.destRect.y = 200;

    }
    if (button_id == 14) {
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

    if (button_id == 13) {
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
    if (button_id == 11) {
//            up movement
//        LOGI("this is %d and button is %d",button_pressed,button_id);
        player.destRect.y -= speed * delta;
    }
    if (button_id == 12) {
//            down movement
//        LOGI("this is %d and button is %d",button_pressed,button_id);
        player.destRect.y += speed * delta;
    }


    player.update(delta);
}


extern "C" int SDL_main(int argc, char *argv[]) {

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) != 0) {
        LOGI("SDL_Init Error: %s", SDL_GetError());
        return 1;
    }

    win = SDL_CreateWindow("SDL Demo",
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





//        LOGI(" FAKE joystick FOUND : %s", SDL_JoystickName(joystick));
//    LOGI(" fale joystick connected : %d", SDL_JoystickOpen());
//    LOGI("joystick connected : %d", SDL_JoystickInstanceID(joystick));



    bool running = true;
    SDL_Event e;

    IMG_Init(IMG_INIT_PNG);

    bg = SDL_LoadBMP("background/background2.bmp");

    // Load texture
    SDL_Texture *playerTexture = IMG_LoadTexture(ren, "player/sprites/new_lugi.png");

    // Create Sprite object
    Sprite player(playerTexture, 100, 100, 64, 64);
    // x=100, y=100, frame width=64, height=64

    player.addAnimation("idle", 1, 4, 2.1f); // row 0, 4 frames, 0.1s per frame
    player.addAnimation("walk", 0, 3,
                        0.2f); // row 0, 4 frames, 0.1s per frame ( less speed value=== fash animetion play like 0.1f)

    if (!playerTexture) {
        LOGI("Failed to load playerr texture : %s", SDL_GetError());
        return 1;
    }

    if (!bg) {
        LOGI("Failed to load BMP BG : %s", SDL_GetError());
        return 1;
    }

    bg_texture = SDL_CreateTextureFromSurface(ren, bg);


    SDL_FreeSurface(surface);
    SDL_FreeSurface(bg);
    lastframetime = SDL_GetTicks();
    fpsTimer = SDL_GetTicks();

    //main game loop
    while (running) {

        float delta = delta_fun();
        fps_counter(delta);

        //loop for events
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;

            if (e.type == SDL_CONTROLLERDEVICEADDED)
                connectController(e.cdevice.which);

            if (e.type == SDL_CONTROLLERDEVICEREMOVED)
                disconnectController(e.cdevice.which);


            if (e.type == SDL_FINGERDOWN) {

            };
        }


        if (controller) {
            isMoving = false;   // har frame reset karo
            if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_UP)) {
                move(SDL_CONTROLLER_BUTTON_DPAD_UP, delta, player);
//                    LOGI("%d",SDL_CONTROLLER_BUTTON_DPAD_RIGHT);

                isMoving = true;   // har frame reset karo

            }
            if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_DOWN)) {
                move(SDL_CONTROLLER_BUTTON_DPAD_DOWN, delta, player);
//                    LOGI("%d",SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
                isMoving = true;   // har frame reset karo

            }
            if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT)) {
                move(SDL_CONTROLLER_BUTTON_DPAD_LEFT, delta, player);
//                    LOGI("%d",SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
                isMoving = true;   // har frame reset karo

            }
            if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT)) {
                move(SDL_CONTROLLER_BUTTON_DPAD_RIGHT, delta, player);
                isMoving = true;   // har frame reset karo

                //                    LOGI("%d",SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
            }
            if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A)) {
                move(SDL_CONTROLLER_BUTTON_A, delta, player);
                isMoving = true;   // har frame reset karo

            }
            if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_B)) {
                move(SDL_CONTROLLER_BUTTON_B, delta, player);
                isMoving = true;   // har frame reset karo


            }

        }


        if (isMoving == false) {
            player.play("idle");
            player.update(delta);  // animation update

        }

//        LOGI("%d", isMoving);
        setup(player, delta);

    }

    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(bg_texture);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
