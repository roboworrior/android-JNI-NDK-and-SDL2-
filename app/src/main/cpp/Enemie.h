
#ifndef ENEMIE_H
#define ENEMIE_H


#include <SDL.h>
#include <string>
#include "Sprite.h"


class Enemie {

public:
    std::string enemie_type="duck";
    SDL_Rect place;
    bool enemie_dead= false;
    bool enemie_ai= false;
    bool enemie_moving= true;
    Sprite enemie_sprite= Sprite(nullptr, 0, 0, 64, 64);
    int temp;
    SDL_Texture *enemie_texture= nullptr;

    // constructor
    Enemie(std::string type , SDL_Rect place);

    // functions
    bool colution_player(SDL_Rect &player) ;
    void playdead(Uint32 stoptime ,float &delta);
    bool colution_dead(SDL_Rect &bullet,Uint32 &time);
    void update(float &delta);
    void render();
    void enemie_move(float &delta);

};




#endif
