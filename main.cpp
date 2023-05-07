#include <iostream>

#include "src/GameEngine.h"

int main() {
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    GameEngine* game = new GameEngine("Battleships", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 850, 400);

    while (game->running()){
        frameStart = SDL_GetTicks();
        // Every frame
       game->handleEvents();
       game->update();
       game->render();

       // Limit frames to FPS value;
       frameTime = SDL_GetTicks() - frameStart;

       if(frameDelay > frameTime){
           SDL_Delay(frameDelay - frameTime);
       }
    }

    game->clean();

    return 0;
}
