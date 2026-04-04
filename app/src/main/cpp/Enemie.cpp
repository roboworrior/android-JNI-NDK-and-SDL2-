//#include "Sprite.h"

#include <SDL_image.h>
#include <SDL.h>
#include "Enemie.h"
#include "globals.h"



Enemie::Enemie(std::string type,SDL_Rect place){
        this->enemie_type= type;
        this->place= place;

        if(enemie_type == "duck"){
            enemie_texture=IMG_LoadTexture(ren, "ememies/green duck.png");

            enemie_sprite.texture= enemie_texture;
            enemie_sprite.destRect={place.x,place.y+8,150,150};
            enemie_sprite.destRect.y-=enemie_sprite.destRect.h;
//            enemie_sprite.destRect.x+=enemie_sprite.destRect.w;
            temp=enemie_sprite.destRect.y;

            enemie_sprite.addAnimation("walk", 0, 4,0.2f); // row 0, 4 frames, 0.1s per frame ( less speed value=== fash animetion play like 0.1f)
            enemie_sprite.addAnimation("death", 1, 4,0.2f); // row 0, 4 frames, 0.1s per frame ( less speed value=== fash animetion play like 0.1f)
        }


    }

bool Enemie:: colution_player(SDL_Rect &player) {
    if(SDL_HasIntersection(&enemie_sprite.destRect,&player)) {

        return true;

        }
        return false;

    }

void Enemie::playdead(Uint32 stoptime ,float &delta){

        if(!enemie_moving){
            Uint32 c_time = SDL_GetTicks()-stoptime;

//           LOGI("this is excuted dead duck");
            if(!enemie_dead){
                enemie_sprite.destRect.y+=150.0*delta;

                if(c_time>=2000){
                    enemie_dead= true;
                }
            }
        }
    }

bool Enemie::colution_dead(SDL_Rect &bullet,Uint32 &time){
        if(SDL_HasIntersection(&enemie_sprite.destRect,&bullet)){

          enemie_sprite.play("death");
          return true;

        }

            return false;
    }


void Enemie::update(float &delta){
        enemie_sprite.update(delta);
    }

void Enemie:: render(){

        if(!enemie_dead) {
            enemie_sprite.render(ren);

        }
        if(enemie_dead) {

            enemie_sprite.destRect.y=temp;
        }

    }


void Enemie:: enemie_move(float &delta){
        if(enemie_moving) {

            enemie_sprite.play("walk");


            if (enemie_sprite.destRect.x <= place.x) {

                enemie_ai = true;

            }

            if (enemie_sprite.destRect.x >= place.x + place.w - enemie_sprite.destRect.w) {
                enemie_ai = false;

            }

            if (enemie_sprite.destRect.x >= place.x - enemie_sprite.destRect.w &&
                enemie_ai == false) {
//            LOGI("going left");
                enemie_sprite.destRect.x -= speed * delta;
                enemie_sprite.setFlip(SDL_FLIP_NONE);
                return;

            }

            if (enemie_sprite.destRect.x != (place.x + place.w) - enemie_sprite.destRect.w &&
                enemie_ai == true) {
//            LOGI("going right");
                enemie_sprite.setFlip(SDL_FLIP_HORIZONTAL);
                enemie_sprite.destRect.x += speed * delta;


                return;

            }

        }
}

