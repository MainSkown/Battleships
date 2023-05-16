#include "GameEngine.h"
#include <iostream>
#include "BattleshipAI.h"

SDL_Renderer *GameEngine::renderer = nullptr;
SDL_Event GameEngine::event;

bool GameEngine::gameEnded = false;
bool GameEngine::playerWon = false;

Round GameEngine::round = PLAYER;

void GameEngine::MapLost(Map *map) {
    gameEnded = true;
    playerWon = !map->isPlayer;
}

void GameEngine::confirm() {
    std::cout << "Confirming" << std::endl;
    if (playerMap->confirm()) {
        uiLayer->DeleteElement(confirmButton);
        secondStage = true;
        enemyMap->confirmed = true;
    }
}

GameEngine::GameEngine(const char *title, int xpos, int ypos, int width, int height) {
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        this->window = SDL_CreateWindow(title, xpos, ypos, width, height, 0);
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer) {
        SDL_SetRenderDrawColor(renderer, 201, 204, 206, 255);
    }

    isRunning = true;

    // Create playerMap
    playerMap = new Map();
    playerMap->isPlayer = true;

    // Create enemyMap
    enemyMap = new Map(417);
    enemyMap->LoadMap();
    enemyMap->isPlayer = false;
    if (!enemyMap->confirm()) {
        throw std::runtime_error("Enemy map is not valid");
    }

    // Start AI
    battleshipAi = new BattleshipAI();
    battleshipAi->init();

    // Create UI
    uiLayer = new UILayer();

    confirmButton = &uiLayer->AddElement<Button>("assets/confirm.png", 256, 396, 128, 32,
                                                 std::bind(&GameEngine::confirm, this));
}

void GameEngine::handleEvents() {
    while (SDL_PollEvent(&event)) {
        if (uiLayer->HasEvent(event.type)) {
            uiLayer->HandleEvent(&event);
        }
        switch (event.type) {
            case SDL_QUIT:
                isRunning = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                int x, y;
                SDL_GetMouseState(&x, &y);
                playerMap->PickGrid(x, y);
                enemyMap->PickGrid(x, y);
                break;
        }
    }
}

void GameEngine::update() {
    playerMap->update();
    uiLayer->update();

    if (round == ENEMY) {
        battleshipAi->Shoot(*playerMap);
        round = PLAYER;
    }
}

void GameEngine::render() {
    SDL_RenderClear(renderer);
    playerMap->draw();
    enemyMap->draw();

    uiLayer->draw();

    if (gameEnded) {
        switch (playerWon) {
            case true:
                break;
            case false:
                break;
        }
    }

    SDL_RenderPresent(renderer);
}

void GameEngine::playerShot() {
    round = ENEMY;
}

void GameEngine::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

GameEngine::~GameEngine() {
    delete playerMap;
    delete enemyMap;
    delete uiLayer;
}