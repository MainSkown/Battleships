#include "GameEngine.h"
#include <iostream>

SDL_Renderer* GameEngine::renderer = nullptr;
SDL_Event GameEngine::event;

bool GameEngine::gameEnded = false;
bool GameEngine::playerWon = false;

void GameEngine::MapLost(Map *map) {
    gameEnded = true;
    playerWon = !map->isPlayer;
}

void GameEngine::confirm() {
    std::cout << "Confirming" << std::endl;
    if(playerMap->confirm()){
        // Then delete button and set game to second stage
    }
}

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
    playerMap->isPlayer = true;
    enemyMap = new Map(417);

    // Create UI
    uiLayer = new UILayer();

    uiLayer->AddElement<Button>("assets/confirm.png", 256, 396, 128, 32, std::bind(&GameEngine::confirm, this));
}

void GameEngine::handleEvents() {
    while(SDL_PollEvent(&event)) {
        if(uiLayer->HasEvent(event.type)){
            uiLayer->HandleEvent(&event);
        }
        switch (event.type) {
            case SDL_QUIT:
                isRunning = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                int x,y;
                SDL_GetMouseState(&x, &y);
                playerMap->PickGrid(x, y);
                enemyMap->PickGrid(x,y);
                break;
            case SDL_KEYDOWN:
                if(event.key.keysym.sym == SDLK_SPACE){
                    if(playerMap->confirm()){
                        std::cout << "Player confirmed" << std::endl;
                    } else {
                        std::cout << "Player not confirmed" << std::endl;
                    }
                }
        }
    }
}

void GameEngine::update() {
    playerMap->update();
    uiLayer->update();
}

void GameEngine::render(){
    SDL_RenderClear(renderer);
    playerMap->draw();
    enemyMap->draw();

    uiLayer->draw();

    if(gameEnded){
        switch (playerWon) {
            case true:
                break;
            case false:
                break;
        }
    }

    SDL_RenderPresent(renderer);
}

void GameEngine::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}