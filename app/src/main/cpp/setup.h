

#include "Sprite.h"
#include "globals.h"




void setup(Sprite &player , Sprite &enemie1 ) {

    int size = 80;
    int margin = size/3;

    player.destRect.h = 150;
    player.destRect.w = 150;

    enemie1.destRect.h = 150;
    enemie1.destRect.w = 150;




    SDL_GetRendererOutputSize(ren, &screen_width, &screen_height);

    dpad  = {10, 405, 312, 312};//   dpad image hight and with and position crop image bysicly main postiion x and y for both dpad and src
    dpad_src = {0, 300, 412,412 };// selection box for dpad

    dpad_left  = {margin, dpad.y+130, size, size};
    dpad_right = {margin + size*2, dpad.y+150, size, size};

    dpad_up    = {margin + size, screen_height - size*3 - margin, size, size};
    dpad_down  = {margin + size, screen_height - size - margin, size, size};


    wall_left  = {-100, 0, 10, screen_height};//   dpad image hight and with and position crop image bysicly main postiion x and y for both dpad and src
    wall_right  = {screen_width+100, 0, 10, screen_height};//   dpad image hight and with and position crop image bysicly main postiion x and y for both dpad and src
    wall_up  = {10, 0, screen_width, 10};//   dpad image hight and with and position crop image bysicly main postiion x and y for both dpad and src
    wall_down  = {0, screen_height-10, screen_width, 10};//   dpad image hight and with and position crop image bysicly main postiion x and y for both dpad and src


    dpad_btn  = {screen_width-400, screen_height-350 , 312, 312};//   dpad image hight and with and position crop image bysicly main postiion x and y for both dpad and src
    dpad_btn_src = {600, 250, 412,412 };// selection box for dpad

    dpad_close  = {700, 0 , 112, 112}; //for box rect main element x,y
    dpad_close_src = {400, 400, 212,212 };// for image

    pipe_src = {930, 330, 212,180 };// for selection reactangle
    pipe_dstrect = {-100, screen_height-220, 412,212 };// for image

    powerup1_dstrect = {-100, -100, 130,130 };// for image
    powerup1_src = {430, 320, 120,120 };// for selection reactangle


    brick_src = {0, 0, 812,280 };// for selection reactangle
    brick_dstrect[0] = {screen_width-700, 190, 712,150 };// for image
    brick_dstrect[1] = {-20, 190, 712,150 };// for image
    brick_dstrect[2] = {(screen_width/2)-250, brick_dstrect[0].y+250, 712,150 };// for image

    brick_dstrect_colustion[0] = {brick_dstrect[0].x, brick_dstrect[0].y,brick_dstrect[0].w ,5 };// for image
    brick_dstrect_colustion[1] = {brick_dstrect[1].x, brick_dstrect[1].y,brick_dstrect[1].w ,5 };// for image
    brick_dstrect_colustion[2] = {brick_dstrect[2].x, brick_dstrect[2].y,brick_dstrect[2].w ,5 };// for image



    coin_src = {130, 300, 170,170};// for selection reactangle

    item1_src = {130, 500, 170,170};// for selection reactangle


    portel1={screen_width-10,0,10,200};

//    for(int i; i<total_bricks; i++){
//        Coin coin;
//        coin.coin_collected= false;
//        coin.coin_dstrect = {0, 200, 120,120};
//        coins.push_back(coin);
//    }

    Item c1;
    c1.item_collected= false;
    c1.item_dstrect={screen_width-500, brick_dstrect[0].y, 120,120 };
    c1.item_dstrect.y-=c1.item_dstrect.h;
    c1.type="coin";
    items.push_back(c1);


    Item c2;
    c2.item_collected= false;
    c2.type="coin";
    c2.item_dstrect = {100, brick_dstrect[0].y, 120,120 };// for image
    c2.item_dstrect.y-=c2.item_dstrect.h;
    items.push_back(c2);

    Item c3;
    c3.item_collected= false;
    c3.type="powerup";
    c3.item_dstrect = {brick_dstrect[2].x+250, brick_dstrect[2].y, 70,70 };// for image
    c3.item_dstrect.y-=c3.item_dstrect.h;
    items.push_back(c3);



//    LOGI("coins %d",coins.size());
//    LOGI("coins %d",coins[0].coin_dstrect.y);
//

    dpad_a  = {dpad_btn.x+25, dpad_btn.y+145, size+20, size+21};
    dpad_b  = {dpad_btn.x+175, dpad_btn.y+145 , size+20, size+21};

    dpad_close_input  = {dpad_close.x+15, dpad_close.y+10 , size, size};

    textRect = {50, 50,200, 50};

    p1_stats.lifes=3;
    p1_stats.coins=0;
    p1_stats.dead_status= false;
    p1_stats.powerup_status= false;
    p1_stats.powerup_fired= false;
    p1_stats.score=0;
    p1_stats.player_flip= false;
    p1_stats.player_win= false;
    player.destRect.x = screen_width/2;
    player.destRect.y = wall_down.y-250;

    enemie1.destRect.x = 300;
    enemie1.destRect.y = 50;

    LOGI("hello this is setup");

//    winrect={0,50,100,100};


}
