#include "GameEngine.h"

SDL_Renderer* GameEngine::renderer = nullptr;
SDL_Event GameEngine::event;

GameEngine::GameEngine(const char *title, int xpos, int ypos, int width, int height) {
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        this->window = SDL_CreateWindow(title, xpos, ypos, width, height, 0);
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if(renderer){
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    }

    isRunning = true;

    // Create playerMap
    playerMap = new Map();
    enemyMap = new Map(417);
}

void GameEngine::handleEvents() {
    while (SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_QUIT:
                isRunning = false;
                break;
        }
    }
}

void GameEngine::update() {

}

void GameEngine::render(){
    SDL_RenderClear(renderer);
    playerMap->draw();
    enemyMap->draw();

    SDL_RenderPresent(renderer);
}

void GameEngine::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}