#include "globals.h"
#include "Sprite.h"


void winingfun(std::string msg){


        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255); //onscreen dpad color
//        SDL_RenderCopy(ren,bg_texture,NULL,NULL);

//        textSurface_win = TTF_RenderText_Blended(font_big,msg.c_str(),green );
        textSurface_win = TTF_RenderText_Blended_Wrapped(font_big,msg.c_str(),green,screen_width );

        winrect={50,50,textSurface_win->w,textSurface_win->h};

    textTexture_win = SDL_CreateTextureFromSurface(ren, textSurface_win);

        SDL_FreeSurface(textSurface_win);



        if(SDL_GameControllerGetButton(controller,SDL_CONTROLLER_BUTTON_START)){

            p1_stats.player_win= false;
            LOGI("reseting game ok");
        }




        SDL_RenderCopy(ren, textTexture_win, NULL, &winrect);



}


void render(Sprite &player, Sprite &enemie1, float &delta) {


    if(!p1_stats.player_win) {

        SDL_RenderClear(ren);
        SDL_RenderCopy(ren, bg_texture, NULL, NULL);

        player.render(ren);   // draw on screen
        if (!enemie_dead) {
            enemie1.render(ren);   // draw on screen

        }


        player_hitbox = {
                player.destRect.x + 20,
                player.destRect.y + player.destRect.h - 10,
                player.destRect.w - 80,
                10
        };


//onscreen control
//    SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);
//    SDL_SetRenderDrawColor(ren, 100, 100, 100, 100); //onscreen dpad color
//    SDL_RenderFillRect(ren,&dpad );
//
//    SDL_SetRenderDrawColor(ren, 255, 0, 100, 255); //onscreen dpad color
//    SDL_RenderFillRect(ren,&dpad_left );
//    SDL_RenderFillRect(ren,&dpad_right );
//
//    SDL_RenderFillRect(ren,&brick_dstrect_colustion[1] );
//    SDL_RenderFillRect(ren,&brick_dstrect_colustion[2] );
//
//    SDL_RenderFillRect(ren,&player_hitbox );
//    SDL_RenderFillRect(ren,&player.destRect );


        SDL_RenderCopy(ren, itemTexture, &pipe_src, &pipe_dstrect);

        SDL_RenderCopy(ren, itemTexture, &brick_src, &brick_dstrect[0]);
        SDL_RenderCopy(ren, itemTexture, &brick_src, &brick_dstrect[1]);
        SDL_RenderCopy(ren, itemTexture, &brick_src, &brick_dstrect[2]);


//    SDL_RenderCopy(ren, itemTexture, &item1_src , &item1_dstrect);

        for (auto &item: items) {

            if (!item.item_collected && item.type == "coin") {
                SDL_RenderCopy(ren, itemTexture, &coin_src, &item.item_dstrect);
            }
            if (!item.item_collected && item.type == "powerup") {

                //its the mystry box use for power ups
                SDL_RenderCopy(ren, itemTexture, &item1_src, &item.item_dstrect);
            }


        }

        for (auto &item: items) {

            if (item.item_collected && item.type == "powerup" && p1_stats.powerup_status == true) {


//            LOGI("this is powerup x :%d and y : %d ",&powerup1_dstrect.x,&powerup1_dstrect.y);
                SDL_RenderCopy(ren, itemTexture, &powerup1_src, &powerup1_dstrect);


            }
        }

        if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A )&& p1_stats.powerup_status){


            if(!p1_stats.powerup_fired){

            powerup1_dstrect.y = player_hitbox.y - player.destRect.h;
            powerup1_dstrect.x = player_hitbox.x;
            }
            p1_stats.powerup_fired= true;
//            p1_stats.powerup_status= false;
//    powerup1_dstrect.x+=speed*delta;


        }


        if (!controller) {
            SDL_RenderCopy(ren, dpad_texture, &dpad_src, &dpad);
            SDL_RenderCopy(ren, dpad_texture, &dpad_btn_src, &dpad_btn);
            SDL_RenderCopy(ren, dpad_texture, &dpad_close_src, &dpad_close);
        }


        SDL_RenderCopy(ren, NULL, NULL, &wall_left);
        SDL_RenderCopy(ren, NULL, NULL, &wall_right);
        SDL_RenderCopy(ren, NULL, NULL, &wall_up);
        SDL_RenderCopy(ren, NULL, NULL, &wall_down);





        //    fps text
        textSurface = TTF_RenderText_Blended(font_small, ("fps :" + std::to_string(fps)).c_str(), yellow);
        textTexture = SDL_CreateTextureFromSurface(ren, textSurface);
        SDL_FreeSurface(textSurface);
        SDL_RenderCopy(ren, textTexture, NULL, &textRect);

        //    fps text
    }
    else{
//        LOGI("you win Lugi go to level 2");
        winingfun("You Win Congrets on clearing level 1 \n\n\nfor restart press [start] for quit press [select] \n this is a demo soon we will upload more levels ");

//        winingfun("this is a demo ");

    }





    SDL_RenderPresent(ren);

    SDL_DestroyTexture(textTexture); // frame ke end pe texture destroy
    SDL_DestroyTexture(textTexture_win); // frame ke end pe texture destroy
}