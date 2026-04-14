

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

    dpad  = {10, screen_height/2, 312, 312};//   dpad image hight and with and position crop image bysicly main postiion x and y for both dpad and src
    dpad_src = {0, 300, 412,412 };// selection box for dpad

    dpad_left  = {margin, dpad.y+dpad.w/2, size, size};
    dpad_left.y-=dpad_left.h/2;
    dpad_right = {margin + size*2+15, dpad.y+dpad.w/2, size, size};
    dpad_right.y-=dpad_right.h/2;
    dpad_up    = {margin + size, screen_height - size*3 - margin, size, size};
    dpad_down  = {margin + size, screen_height - size - margin, size, size};


    wall_left  = {-100, 0, 10, screen_height};//   dpad image hight and with and position crop image bysicly main postiion x and y for both dpad and src
    wall_right  = {screen_width+100, 0, 10, screen_height};//   dpad image hight and with and position crop image bysicly main postiion x and y for both dpad and src
    wall_up  = {10, 0, screen_width, 10};//   dpad image hight and with and position crop image bysicly main postiion x and y for both dpad and src
    wall_down  = {0, screen_height-10, screen_width, 10};//   dpad image hight and with and position crop image bysicly main postiion x and y for both dpad and src


    dpad_btn  = {screen_width-400, screen_height-350 , 312, 312};//   dpad image hight and with and position crop image bysicly main postiion x and y for both dpad and src
    dpad_btn_src = {600, 250, 412,412 };// selection box for dpad

    dpad_close  = {screen_width/2, 0 , 300, 200}; //for box rect main element x,y
    dpad_close.x-=dpad_close.w/2;
    dpad_close_src = {0, 0, 400,250 };// for image

    pipe_src = {930, 330, 212,180 };// for selection reactangle
    pipe_dstrect = {-100, screen_height-220, 412,212 };// for image

    powerup1_dstrect = {-100, -100, 130,130 };// for image
    powerup1_src = {430, 320, 120,120 };// for selection reactangle



    msg_box={screen_width/2,screen_height/2,screen_width/2,screen_height/2};
    msg_box.x-=msg_box.w/2;
    msg_box.y-=msg_box.h/2;



    coin_src = {130, 300, 170,170};// for selection reactangle

    item1_src = {130, 500, 170,170};// for selection reactangle


    portel1={0,0,20,200};


    dpad_a  = {dpad_btn.x+25, dpad_btn.y+145, size+20, size+21};
    dpad_b  = {dpad_btn.x+175, dpad_btn.y+145 , size+20, size+21};

    dpad_close_input  = {dpad_close.x+25, dpad_close.y+25 , size, size};
    dpad_close_start  = {dpad_close_input.x+size*2+15, dpad_close_input.y , size, size};

//    dpad_close_input.x+=dpad_close_input.w;


    textRect = {50, 50,200, 50};

    p1_stats.lifes=3;
    p1_stats.coins=0;
    p1_stats.dead_status= false;
    p1_stats.powerup_status= false;
    p1_stats.powerup_fired= false;
    p1_stats.score=0;
    p1_stats.player_flip= false;
    p1_stats.player_win= true;

    player.destRect.x = 0;
    player.destRect.y = 0;

    enemie1.destRect.x = 300;
    enemie1.destRect.y = brick_dstrect[1].y-enemie1.destRect.h;

    tile_brick.dest={0,0,128,128}; //render rect size that render on display
    tile_brick.src={20,0,224,224}; //main image sorce full use full resalution
    tile_brick.type="brick";

    LOGI("hello this is setup");

//    winrect={0,50,100,100};



    for(int i=0;i<total_bricks;i++) {
        Enemie enem("duck",brick_dstrect[i]);

        enem.enemie_sprite.destRect.x+=i*speed;
        enemies.push_back(enem);
    }

    p1_stats.level_render= false;

    //////////////////////////////

    int total_brick_w;

    int level1[6][12]={
             2,0,4,3,0,0,0,0,0,4,0,2
            ,1,1,1,1,1,0,0,1,1,1,1,1
            ,0,0,0,6,0,4,0,0,0,0,0,0
            ,0,0,0,1,1,1,1,1,1,0,0,0
            ,2,0,0,4,0,5,0,0,0,0,0,2


    };
    int rows = sizeof(level1) / sizeof(level1[0]);
    int cols = sizeof(level1[0]) / sizeof(level1[0][0]);

    int portal_count=0;

    for (int i = 0; i <rows; i++) {
        tile_brick.dest.y=i*tile_brick.dest.h;

        for (int j = 0; j <cols;j++) {
            if(level1[i][j]==0){
//                0 is for empty
                continue;
            }
            if(level1[i][j]==1){

//                1 is for brick
                tile_brick.dest.x=j*(tile_brick.dest.w);
//                tile_brick.dest.x+=50;


                Tile_obj b1;
                b1.type="brick";
                b1.dest.x=tile_brick.dest.x;
                b1.dest.y=tile_brick.dest.y;
                b1.dest.h=tile_brick.dest.h;
                b1.dest.w=tile_brick.dest.w;
                b1.src=tile_brick.src;
                tiles.push_back(b1);


            }
            if(level1[i][j]==2){
//                0 is for pipe /or portal

                portal_count+=1;
                tile_brick.dest.x=j*(tile_brick.dest.w);
//                tile_brick.dest.x+=50;

                Tile_obj t1;
                t1.type="portal";
                t1.dest.x=tile_brick.dest.x;
                t1.dest.y=tile_brick.dest.y;
                t1.dest.h=200;
                t1.dest.w=50;
                t1.id= to_string(i)+to_string(j);

//                t1.src={20,0,224,224};
                tiles.push_back(t1);

            }

            if(level1[i][j]==3){
//                3 is for enemie
                Enemie enem("duck",brick_dstrect[i]);
                enemies.push_back(enem);


                Tile_obj t1;
                t1.type="enemie";

//                t1.src={20,0,224,224};
                tiles.push_back(t1);

            }
            if(level1[i][j]==5){
//                3 is for player
                tile_brick.dest.x=j*(tile_brick.dest.w);
                tile_brick.dest.x+=50;

                player.destRect.x=tile_brick.dest.x;
                player.destRect.y=tile_brick.dest.y;
            }
            if(level1[i][j]==4){
//                0 is for coin
                tile_brick.dest.x=j*(tile_brick.dest.w);
                tile_brick.dest.x+=50;

                Tile_obj t1;
                t1.type="coin";
                t1.dest.x=tile_brick.dest.x;
                t1.dest.y=tile_brick.dest.y+20;
                t1.dest.h=128;
                t1.dest.w=128;
                t1.src=coin_src;
                tiles.push_back(t1);
            }
            if(level1[i][j]==6){
//        this is for powerup
                tile_brick.dest.x=j*(tile_brick.dest.w);
                tile_brick.dest.x+=50;

                Tile_obj t1;
                t1.type="powerup";
                t1.dest.x=tile_brick.dest.x;
                t1.dest.y=tile_brick.dest.y+50;
                t1.dest.h=100;
                t1.dest.w=100;
                t1.src=item1_src;
                tiles.push_back(t1);
            }




        }

    }
    ///////////////////////////

    Tile_obj *tile_pointer=NULL;

    for(auto &tile :tiles){

        if(tile.type== "portal"){
            if(tile_pointer==NULL){

                tile_pointer=&tile;
                continue;
            }

            if(tile_pointer!=NULL){

                tile.go_to.x=tile_pointer->dest.x;
                tile.go_to.y=tile_pointer->dest.y;


                tile_pointer->go_to.x=tile.dest.x;
                tile_pointer->go_to.y=tile.dest.y;



                if(tile.go_to.x>screen_width/2) {
                    tile.go_to.x-=150;
                }
                if(tile_pointer->go_to.x>screen_width/2) {
                    tile_pointer->go_to.x-=150;
                }


                if(tile.go_to.x<screen_width/2) {
                    tile.go_to.x+=150;
                }
                if(tile_pointer->go_to.x<screen_width/2) {
                    tile_pointer->go_to.x+=150;
                }



                //this is height

                if(tile.go_to.y>screen_height/2) {
                    tile.go_to.y=0;

                }

                if(tile_pointer->go_to.y>screen_height/2) {
                    tile_pointer->go_to.y=0;
                }

//                if(tile.go_to.y<screen_height/2) {
//                    tile.go_to.y=screen_height-250;
//
//                }
//
//                if(tile_pointer->go_to.y<screen_height/2) {
//                    tile_pointer->go_to.y=screen_height-250;
//                }






                LOGI("tile goto x :%d goto y :%d",tile.go_to.x,tile.go_to.y);
                LOGI("tile_pointer goto x :%d goto y :%d",tile_pointer->go_to.x,tile_pointer->go_to.y);
                tile_pointer=NULL;
            }
        }

    }

}
