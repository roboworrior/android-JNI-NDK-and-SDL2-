#include "globals.h"

SDL_Renderer *ren = nullptr;
SDL_Window *win = nullptr;

SDL_Rect dpad_right;
SDL_Rect dpad_left;
SDL_Rect dpad_up;
SDL_Rect dpad_down;

SDL_Rect portel1;

TTF_Font* font = nullptr;
SDL_Rect dpad_a;
SDL_Rect dpad_b;
SDL_Rect dpad_close_input;

std::vector<Item> items;

SDL_Rect coin_src;
SDL_Rect item1_src;
SDL_Rect item1_dstrect;
SDL_Rect powerup1_src;
SDL_Rect powerup1_dstrect;

SDL_Rect dpad_close;
int score = 0;

SDL_Rect dpad;
SDL_Rect wall_left;
SDL_Rect wall_up;
SDL_Rect wall_down;
SDL_Rect wall_right;
SDL_Rect dpad_btn;
SDL_Rect textRect;

SDL_Rect dpad_src;
SDL_Rect dpad_btn_src;

SDL_Rect player_hitbox;
SDL_Rect dpad_close_src;

SDL_Rect pipe_src;
SDL_Rect pipe_dstrect;

SDL_Rect brick_src;

SDL_Rect brick_dstrect[total_bricks];

SDL_Color yellow = {255, 255, 0, 255};

SDL_GameController *controller = nullptr;

SDL_Texture *bg_texture = nullptr;
SDL_Texture *dpad_texture = nullptr;
SDL_Texture *textTexture = nullptr;
SDL_Surface* textSurface = nullptr;
SDL_Texture *playerTexture = nullptr;
SDL_Texture *enemie1Texture = nullptr;
SDL_Texture *itemTexture = nullptr;
SDL_Surface* bg = nullptr;

int screen_width = 0;
int screen_height = 0;

bool button_pressed = false;
bool enemie_ai = false;

bool vsync = false;
bool player_flip = false;
Uint32 lastframetime = 0;
bool isMoving = false;
bool player_onair = false;
int fps = 0;

std::string onscreen_control = "none";
int frameCount = 0;
Uint32 fpsTimer = 0;
float speed = 450.0f;

int red = 255;
int green = 0;
int blue = 0;
