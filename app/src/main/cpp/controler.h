#include <SDL.h>
#include "globals.h"

//controler login
void connectController(int index) {

    if (!SDL_IsGameController(index)) return;

    controller = SDL_GameControllerOpen(index);

    if (controller) {
        LOGI("Controller Connected : %s",
             SDL_GameControllerName(controller));
    }
}


void disconnectController(SDL_JoystickID id) {

    if (!controller) return;

    SDL_Joystick *joy =
            SDL_GameControllerGetJoystick(controller);

    if (SDL_JoystickInstanceID(joy) == id) {

        SDL_GameControllerClose(controller);
        controller = NULL;

        LOGI("Controller Removed");
    }
}

//controler login


