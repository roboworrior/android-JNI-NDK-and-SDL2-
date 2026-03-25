#include "globals.h"
#include "Sprite.h"




void msg_fun(std::string msg){


        SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);

        SDL_SetRenderDrawColor(ren,0, 0, 0, 200); //onscreen dpad color

        SDL_RenderFillRect(ren, &msg_box);

        textSurface_win = TTF_RenderText_Blended_Wrapped(font_small, msg.c_str(), green,
                                                         msg_box.w - 50);

        winrect = {msg_box.x + 50, msg_box.y + 50, textSurface_win->w, textSurface_win->h};

        textTexture_win = SDL_CreateTextureFromSurface(ren, textSurface_win);

        SDL_FreeSurface(textSurface_win);
        SDL_RenderCopy(ren, textTexture_win, NULL, &winrect);

}

void render(Sprite &player, Sprite &enemie1, float &delta) {



        SDL_RenderClear(ren);



    if(!p1_stats.player_win) {

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
        if(p1_stats.msg_triggered){

        current_time = SDL_GetTicks() - timer;

        if(current_time<=5000) {
            msg_fun("You Win Congrets on clearing level 1");
//            LOGI("this is 1 msg current timer %d:  ,timer :%d",current_time,timer);
        }

        if(current_time >(5000) && current_time<=(10000)) {
            msg_fun("this is a demo soon we will upload more levels");
//            LOGI("this is 2 msg current timer %d:  ,timer :%d",current_time,timer);
        }
        if(current_time >(10000) && !controller) {
            msg_fun("for restart press [START] for quit press [X]");
//            LOGI("this is 3 msg current timer %d:  ,timer :%d",current_time,timer);
        }
        if(current_time >(10000) && controller) {
            msg_fun("for restart press [START] for quit press [SELECT]");
//            LOGI("this is 3 msg current timer %d:  ,timer :%d",current_time,timer);
        }

        }




    }



    if (!controller) {
        SDL_RenderCopy(ren, dpad_texture, &dpad_src, &dpad);
        SDL_RenderCopy(ren, dpad_texture, &dpad_btn_src, &dpad_btn);
        SDL_RenderCopy(ren, dpad_texture, &dpad_close_src, &dpad_close);
    }


    if(SDL_GetTicks()-timer<5000 && p1_stats.msg_triggered== false) {

        msg_fun("colllect all the coins to win the game");
    }

    SDL_RenderPresent(ren);

  SDL_DestroyTexture(textTexture_win); // frame ke end pe texture destroy
    SDL_DestroyTexture(textTexture); // frame ke end pe texture destroy

}
