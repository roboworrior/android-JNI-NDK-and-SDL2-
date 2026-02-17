#include <jni.h>
#include <android/log.h>
#include <cstdlib>
#include <random>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <SDL_ttf.h>


#include "Sprite.h"


#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "SDL_DEMO", __VA_ARGS__))



SDL_Renderer *ren = NULL;
SDL_Window *win = NULL;

SDL_Rect dpad_right;
SDL_Rect dpad_left;
SDL_Rect dpad_up;
SDL_Rect dpad_down;

TTF_Font* font;
SDL_Rect dpad_a;
SDL_Rect dpad_b;

SDL_Rect dpad;
SDL_Rect dpad_btn;
SDL_Rect textRect;
SDL_Rect dpad_src;
SDL_Rect dpad_btn_src;

SDL_Color yellow = {255,255,0,255};

SDL_GameController *controller = NULL;

SDL_Surface *bg;
SDL_Texture *bg_texture;
SDL_Texture *dpad_texture;
SDL_Texture *textTexture;
SDL_Surface* textSurface;

int screen_width, screen_height;


bool button_pressed = false;
bool vsync = false;
bool player_flip = false;
Uint32 lastframetime = 0;
bool isMoving = false;   // har frame reset karo
int fps = 0;

std::string onscreen_control="none";
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
        LOGI("Controller Connected : %s",
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

void setup(Sprite &player) {

    int size = 80;
    int margin = size/3;

    player.destRect.h = 250;
    player.destRect.w = 250;

    dpad_left  = {margin, screen_height - size*2 - margin, size, size};
    dpad_right = {margin + size*2, screen_height - size*2 - margin, size, size};
    dpad_up    = {margin + size, screen_height - size*3 - margin, size, size};
    dpad_down  = {margin + size, screen_height - size - margin, size, size};

    dpad_a  = {screen_width-275, screen_height-200, size+20, size+10};
    dpad_b  = {screen_width-125, screen_height-200 , size+20, size+10};


    dpad  = {10, 405, 312, 312};//   dpad image hight and with and position crop image bysicly main postiion x and y for both dpad and src
    dpad_src = {0, 300, 412,412 };// selection box for dpad

    dpad_btn  = {screen_width-300, screen_height-350 , 312, 312};//   dpad image hight and with and position crop image bysicly main postiion x and y for both dpad and src
    dpad_btn_src = {600, 250, 412,412 };// selection box for dpad

    textRect = {50, 50,200, 50};



}
void render(Sprite &player, float &delta) {

    SDL_RenderClear(ren);
    SDL_RenderCopy(ren, bg_texture, NULL, NULL);
    player.render(ren);   // draw on screen
//    canvas
//    SDL_SetRenderDrawColor(ren, 100, 255, 2, 255);

//onscreen control
    SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(ren, 100, 100, 100, 0); //onscreen dpad color

    SDL_RenderFillRect(ren,&dpad_right );
    SDL_RenderFillRect(ren,&dpad_left );
    SDL_RenderFillRect(ren,&dpad_up );
    SDL_RenderFillRect(ren,&dpad_down );

    SDL_RenderFillRect(ren,&dpad_a );
    SDL_RenderFillRect(ren,&dpad_b );

    SDL_RenderFillRect(ren,&dpad ); // is for selection rectangel
    SDL_RenderFillRect(ren,&dpad_btn ); // is for selection rectangel
//onscreen control

//    fps text

     textSurface = TTF_RenderText_Blended(font, ("fps :" + std::to_string(fps)).c_str()  , yellow);
    textTexture = SDL_CreateTextureFromSurface(ren, textSurface);

//    fps text

    SDL_RenderCopy(ren, textTexture, NULL, &textRect);
    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);

    SDL_RenderCopy(ren, dpad_texture, &dpad_src, &dpad);
    SDL_RenderCopy(ren, dpad_texture,&dpad_btn_src , &dpad_btn);

        SDL_RenderPresent(ren);

}

void move(int button_id, float &delta, Sprite &player) {

//    if(delta>=7.008000){delta=7.008000;}

    if (button_id == 3) {
        hello();
    }

    if (button_id == 734) {

        if (vsync == false) {
            vsync = true;
            LOGI("vsyn on");

        }
        if (vsync == true) {
            vsync = false;
            LOGI("vsyn off");

        }

    }

    if (button_id == 0) {
        //reset player
        player.destRect.x = 250;
        player.destRect.y = 200;

    }
    if (button_id == 1) {
        //reset player
        player.play("jump");
    }
    if (button_id == 14) {
//            right movement

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


//    player.update(delta);
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


    SDL_GetRendererOutputSize(ren, &screen_width, &screen_height);

    bool running = true;
    SDL_Event e;

    IMG_Init(IMG_INIT_PNG);
     TTF_Init();
     font = TTF_OpenFont("fonts/Noto_Sans/static/NotoSans-Bold.ttf", 50);

    if(!font){
        LOGI("font not found");
        return 1;
    }




    bg = SDL_LoadBMP("background/background2.bmp");

    // Load texture
    SDL_Texture *playerTexture = IMG_LoadTexture(ren, "player/sprites/new_lugi.png");
    dpad_texture = IMG_LoadTexture(ren, "on screen control/dpad1.png");
    bg_texture = SDL_CreateTextureFromSurface(ren, bg);



    // Create Sprite object
    Sprite player(playerTexture, 100, 100, 64, 64);
    // x=100, y=100, frame width=64, height=64

    player.addAnimation("idle", 1, 4, 2.1f); // row 0, 4 frames, 0.1s per frame
    player.addAnimation("jump", 2, 3,0.2f); // row 0, 4 frames, 0.1s per frame ( less speed value=== fash animetion play like 0.1f)
    player.addAnimation("walk", 0, 3,0.2f); // row 0, 4 frames, 0.1s per frame ( less speed value=== fash animetion play like 0.1f)

    if (!playerTexture) {
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



    SDL_FreeSurface(bg);
    lastframetime = SDL_GetTicks();
    fpsTimer = SDL_GetTicks();


    setup(player);

    //main game loop
    while (running) {

        float delta = delta_fun();
         fps_counter(delta);
//        LOGI("fps : %d", fps_counter(delta));


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

        }




        render(player, delta);

        player.update(delta);  // animation update

        if(onscreen_control == "none") {
                isMoving= false;
        }
        if(onscreen_control == "left"){

            isMoving= true;
            move(SDL_CONTROLLER_BUTTON_DPAD_LEFT,delta,player);
            }
        if(onscreen_control == "right"){

            isMoving= true;
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


        if (isMoving == false) {
            player.play("idle");

        }



//        LOGI("%d", isMoving);


    }


    SDL_DestroyTexture(bg_texture);
    SDL_DestroyTexture(dpad_texture);
    SDL_DestroyTexture(playerTexture);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
