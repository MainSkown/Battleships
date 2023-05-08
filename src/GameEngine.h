#ifndef BATTLESHIPS_GAMEENGINE_H
#define BATTLESHIPS_GAMEENGINE_H

#include <SDL.h>
#include "Map.h"
#include "UI/UIElements.h"

enum Round {
    PLAYER,
    ENEMY
};

class GameEngine {
private:
    bool isRunning;
    SDL_Window *window;
    Map* playerMap, *enemyMap;
    static bool gameEnded;
    static bool playerWon;
    UILayer* uiLayer;
    Button *confirmButton;
    bool secondStage = false;

public:
    static Round round;
    GameEngine(const char* title, int xpos, int ypos, int width, int height);
    ~GameEngine();

    bool running() { return isRunning; }

    void handleEvents();
    void update();
    void render();
    void clean();

    static SDL_Renderer* renderer;
    static SDL_Event event;
    static void MapLost(Map* map);
    void confirm();
    static void playerShot();
};


#endif //BATTLESHIPS_GAMEENGINE_H
