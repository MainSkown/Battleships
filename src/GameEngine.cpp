#include "GameEngine.h"

SDL_Renderer* GameEngine::renderer = nullptr;
SDL_Event GameEngine::event;

GameEngine::GameEngine(const char *title, int xpos, int ypos, int width, int height) {
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        this->window = SDL_CreateWindow(title, xpos, ypos, width, height, 0);
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if(renderer){
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    }

    isRunning = true;

    // Create map etc.
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

    SDL_RenderPresent(renderer);
}

void GameEngine::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}