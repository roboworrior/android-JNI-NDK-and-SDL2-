#include "globals.h"
#include "Sprite.h"
void move(int button_id, float &delta, Sprite &player) {

//    LOGI("button : %d", button_id);

    //colustions

    for(auto &item :items){

        if(!item.item_collected && SDL_HasIntersection(&player.destRect, &item.item_dstrect)){
            item.item_collected= true;

            if(item.type == "coin"){
                score+=50;
            }
            if(item.type == "powerup"){
                speed+=100;
            }

            LOGI("Player Score : %d",score);

        }

    }

    if(SDL_HasIntersection(&player.destRect, &portel1)){
        player.destRect.x=50;

    }

    if(SDL_HasIntersection(&player.destRect, &wall_left))
    {
//        LOGI("player enter in wall");
        player.destRect.x+=10;
        return;

    }
    if(SDL_HasIntersection(&player.destRect, &wall_right))
    {
//        LOGI("player enter in wall");
        player.destRect.x-=10;
        return;

    }

    if(SDL_HasIntersection(&player.destRect, &wall_up))
    {
//        LOGI("player enter in wall");
        player.destRect.y+=10;
        return;

    }


    if(SDL_HasIntersection(&player_hitbox , &pipe_dstrect) ){
        LOGI("this is pipe");

        player.destRect.y=(brick_dstrect[0].y-250);
        player.destRect.x=screen_width-200;


    }




    if(SDL_HasIntersection(&player.destRect, &wall_down ))
    {
        player.destRect.y-=10;
        return;
    }

//cloutions end


    if (button_id == 2 || button_id == 3) {
//        cleanup();
    }



    if (button_id == 6) {
        //reset player
        player.destRect.x = screen_width/2;
        player.destRect.y = wall_down.y-250;
        speed= 450.0f;

        for(auto &item :items){
            item.item_collected= false;

        }

    }

    if (button_id == 1) {
        //reset player

        player.play("jump");

    }
    if (button_id == 0) {

        player_onair= true;
        player.destRect.y -= 50;


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

void enem_move(Sprite &enemie1, SDL_Rect &place, float &delta,Sprite &player){
    enemie1.play("walk");

    if(SDL_HasIntersection(&player_hitbox , &enemie1.destRect) ) {
        LOGI("dont tuch me lugi ");
        move(6,delta,player);
    }

//    LOGI("place.x : %d  and player.x : %d enimie_ai is :%d",place.x,enemie1.destRect.x,enemie_ai);

    if(enemie1.destRect.x <= place.x-enemie1.destRect.w){
        enemie_ai= true;

    }
    if(enemie1.destRect.x >= place.x+place.w-enemie1.destRect.w){
        enemie_ai= false;

    }

        if(enemie1.destRect.x >= place.x-enemie1.destRect.w && enemie_ai== false){
//            LOGI("going left");
            enemie1.destRect.x -= speed * delta;
            enemie1.setFlip(SDL_FLIP_NONE);
            return;

        }
        if(enemie1.destRect.x != (place.x+place.w)-enemie1.destRect.w && enemie_ai== true){
//            LOGI("going right");
            enemie1.setFlip(SDL_FLIP_HORIZONTAL);
            enemie1.destRect.x += speed * delta;


            return;

        }






}
