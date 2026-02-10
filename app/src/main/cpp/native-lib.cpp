#include <jni.h>
#include <SDL.h>
#include <android/log.h>
#include <cstdlib>
#include <random>
#include <iostream>


#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "SDL_DEMO", __VA_ARGS__))
SDL_Renderer* ren=NULL;
SDL_Joystick* joystick= NULL;
SDL_Rect ball;

bool button_pressed=false;
Uint32 lastframetime = 0;
int buttonpressis=99;
int fps = 0;
int frameCount = 0;
Uint32 fpsTimer = 0;
float speed = 800.0f;





int red =255;
int green ;
int blue ;


int random_number() {
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 255);
    return dist(gen);
}

void hello(){
    red=random_number();
    green=random_number();
    blue=random_number();
}
void setup(){





//    background
    SDL_SetRenderDrawColor(ren,255,255,255,255);
    SDL_RenderClear(ren);
//    background



    SDL_SetRenderDrawColor(ren,red,green,blue,255);
    SDL_RenderFillRect(ren,&ball);
//   ball

    SDL_RenderPresent(ren);


}

void movestick(int stick_type, int stick_value){
    if(stick_type==0 and stick_value>0){
//        RIGHT
////        LOGI("RIGHT");
        ball.x+=20;

    }

    if(stick_type==1 and stick_value>0){
//        DOWN

        ball.y+=20;
    }

    if(stick_type==1 and stick_value<0){
//        UP MOVEMENT

        ball.y-=20;
    }


    if(stick_type==0 and stick_value<0){
        //Left movement

        ball.x-=20;
    }

}

void move(int button_id ,float delta){


//    if(delta>=7.008000){delta=7.008000;}

    if(button_pressed==1 and button_id==3) {
        hello();
    }
    if(button_pressed==1 and button_id==2){
        ball.x=250;
        ball.y=200;
    }
    if(button_pressed==1 and button_id==14){
//            right movement
//        LOGI("this is %d and button is %d",button_pressed,button_id);
        ball.x+=speed*delta;
    }
    if(button_pressed==1 and button_id==13){
//            left movement
//        LOGI("this is %d and button is %d",button_pressed,button_id);
        ball.x-=speed*delta;
    }
    if(button_pressed==1 and button_id==11){
//            up movement
//        LOGI("this is %d and button is %d",button_pressed,button_id);
        ball.y-=speed*delta;
    }
    if(button_pressed==1 and button_id==12){
//            down movement
//        LOGI("this is %d and button is %d",button_pressed,button_id);
        ball.y+=speed*delta;
    }


}



extern "C" int SDL_main(int argc, char *argv[]) {

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        LOGI("SDL_Init Error: %s", SDL_GetError());
        return 1;
    }

    SDL_Window* win = SDL_CreateWindow("SDL Demo",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       640, 480,
                                       SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);


    if (!win) {
        LOGI("SDL_CreateWindow Error: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

     ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED );




    if (!ren) {
        SDL_DestroyWindow(win);
        LOGI("SDL_CreateRenderer Error: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    if(SDL_NumJoysticks()<0){

        LOGI("JOYSTICK NOT FOUND");
    }
    joystick=SDL_JoystickOpen(0);
    LOGI("joystick FOUND : %s",SDL_JoystickName(joystick));

    LOGI("joystick connected : %d", SDL_JoystickInstanceID(joystick));


    // Main loop (render red screen)
    bool running = true;
    SDL_Event e;


    ball.y=200;
    ball.x=250;
    ball.w=100;
    ball.h=100;

     lastframetime = SDL_GetTicks();
    fpsTimer = SDL_GetTicks();
    while (running) {

//        delta
        Uint32 now = SDL_GetTicks();
        float delta = (now - lastframetime) / 1000.0f;
          lastframetime = now;

//        delta = SDL_clamp(delta, 0.0f, 0.05f);
//        delta

//fps
        frameCount++;

        if (SDL_GetTicks() - fpsTimer >= 1000) {
            LOGI("FPS: %d \nDELTA : %f", frameCount,delta);
            frameCount = 0;
            fpsTimer = SDL_GetTicks();
        }
//fps


        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;
            if (e.type == SDL_JOYAXISMOTION) {
                    LOGI("JOYSTICK %d moving %d",e.jaxis.axis, e.jaxis.value);
                    movestick(e.jaxis.axis,e.jaxis.value);
            }
            if (e.type == SDL_JOYBUTTONUP) {
                button_pressed=false;
                LOGI("JOYSTICK Button up %d ",e.jbutton.button);


            }
            if (e.type == SDL_JOYBUTTONDOWN) {

                button_pressed=true;
                LOGI("button_pressed %d",e.jbutton.button);
//                      move_button(e.jbutton.button);
                        buttonpressis=e.jbutton.button;
//                )


            }


//            if (e.type == SDL_FINGERDOWN){
//                hello();
//            };
        }



//        SDL_RenderFillRect(ren, &rectangel);


        move(buttonpressis,delta );
        setup();


    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
