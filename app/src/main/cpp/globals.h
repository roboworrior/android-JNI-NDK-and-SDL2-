#ifndef GLOBALS_H
#define GLOBALS_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>

extern SDL_Renderer *ren;
extern SDL_Window *win;

extern SDL_Rect dpad_right;
extern SDL_Rect dpad_left;
extern SDL_Rect dpad_up;
extern SDL_Rect dpad_down;

extern SDL_Rect portel1;

extern TTF_Font* font;
extern SDL_Rect dpad_a;
extern SDL_Rect dpad_b;
extern SDL_Rect dpad_close_input;

struct Item {
    SDL_Rect item_dstrect;
    bool item_collected = false;
    std::string type;
};

extern std::vector<Item> items;

extern SDL_Rect coin_src;
extern SDL_Rect item1_src;
extern SDL_Rect item1_dstrect;
extern SDL_Rect powerup1_src;
extern SDL_Rect powerup1_dstrect;

extern SDL_Rect dpad_close;
extern int score;

extern SDL_Rect dpad;
extern SDL_Rect wall_left;
extern SDL_Rect wall_up;
extern SDL_Rect wall_down;
extern SDL_Rect wall_right;
extern SDL_Rect dpad_btn;
extern SDL_Rect textRect;

extern SDL_Rect dpad_src;
extern SDL_Rect dpad_btn_src;

extern SDL_Rect player_hitbox;
extern SDL_Rect dpad_close_src;

extern SDL_Rect pipe_src;
extern SDL_Rect pipe_dstrect;

extern SDL_Rect brick_src;

const int total_bricks = 3;
extern SDL_Rect brick_dstrect[total_bricks];
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "SDL_DEMO", __VA_ARGS__))


extern SDL_Color yellow;

extern SDL_GameController *controller;

extern SDL_Texture *bg_texture;
extern SDL_Texture *dpad_texture;
extern SDL_Texture *textTexture;
extern SDL_Surface* textSurface;
extern SDL_Texture *playerTexture;
extern SDL_Texture *enemie1Texture;
extern SDL_Texture *itemTexture;
extern SDL_Surface* bg;

extern int screen_width, screen_height;

extern bool button_pressed;
extern bool vsync;
extern bool player_flip;
extern Uint32 lastframetime;
extern bool isMoving;
extern bool player_onair;
extern bool enemie_ai;
extern int fps;

extern std::string onscreen_control;
extern int frameCount;
extern Uint32 fpsTimer;
extern float speed;

extern int red;
extern int green;
extern int blue;

#endif
