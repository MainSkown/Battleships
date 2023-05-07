#ifndef BATTLESHIPS_GAMEENGINE_H
#define BATTLESHIPS_GAMEENGINE_H

#include <SDL.h>
#include "Map.h"

class GameEngine {
private:
    bool isRunning;
    SDL_Window *window;
    Map* playerMap, *enemyMap;

public:
    GameEngine(const char* title, int xpos, int ypos, int width, int height);
    ~GameEngine();

    bool running() { return isRunning; }

    void handleEvents();
    void update();
    void render();
    void clean();

    static SDL_Renderer* renderer;
    static SDL_Event event;
};


#endif //BATTLESHIPS_GAMEENGINE_H
