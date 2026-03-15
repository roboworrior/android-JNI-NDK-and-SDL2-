#include "globals.h"
#include "Sprite.h"

void render(Sprite &player, Sprite &enemie1, float &delta) {

    SDL_RenderClear(ren);
    SDL_RenderCopy(ren, bg_texture, NULL, NULL);

    player.render(ren);   // draw on screen
    enemie1.render(ren);   // draw on screen


    player_hitbox = {
            player.destRect.x + 10,
            player.destRect.y + player.destRect.h - 10,
            player.destRect.w - 25,
            10
    };


//onscreen control
//    SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);
//    SDL_SetRenderDrawColor(ren, 100, 100, 100, 100); //onscreen dpad color
//
//    SDL_RenderFillRect(ren,&brick_dstrect[1] );
//    SDL_RenderFillRect(ren,&brick_dstrect[1] );


    SDL_RenderCopy(ren, itemTexture,&pipe_src , &pipe_dstrect);

    SDL_RenderCopy(ren, itemTexture,&brick_src , &brick_dstrect[0]);
    SDL_RenderCopy(ren, itemTexture,&brick_src , &brick_dstrect[1]);
    SDL_RenderCopy(ren, itemTexture,&brick_src , &brick_dstrect[2]);


//    SDL_RenderCopy(ren, itemTexture, &item1_src , &item1_dstrect);

    for(auto &item: items){

        if(!item.item_collected && item.type=="coin" ){
            SDL_RenderCopy(ren, itemTexture,&coin_src , &item.item_dstrect);
        }
        if(!item.item_collected && item.type=="powerup" ){
            SDL_RenderCopy(ren, itemTexture,&item1_src , &item.item_dstrect);
        }

    }

    for(auto &item: items) {

        if(item.item_collected && item.type=="powerup" ) {

            SDL_RenderCopy(ren, itemTexture, &powerup1_src, &powerup1_dstrect);
        }
    }

    if(!controller){
        SDL_RenderCopy(ren, dpad_texture, &dpad_src, &dpad);
        SDL_RenderCopy(ren, dpad_texture,&dpad_btn_src , &dpad_btn);
        SDL_RenderCopy(ren, dpad_texture,&dpad_close_src , &dpad_close);
    }



    SDL_RenderCopy(ren, NULL,NULL , &wall_left);
    SDL_RenderCopy(ren, NULL,NULL , &wall_right);
    SDL_RenderCopy(ren, NULL,NULL , &wall_up);
    SDL_RenderCopy(ren, NULL,NULL , &wall_down);


    //    fps text
    textSurface = TTF_RenderText_Blended(font, ("fps :" + std::to_string(fps)).c_str()  , yellow);
    textTexture = SDL_CreateTextureFromSurface(ren, textSurface);
    SDL_FreeSurface(textSurface);
    SDL_RenderCopy(ren, textTexture, NULL, &textRect);
//    fps text


    SDL_RenderPresent(ren);

    SDL_DestroyTexture(textTexture); // frame ke end pe texture destroy
}