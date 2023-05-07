#ifndef BATTLESHIPS_MAP_H
#define BATTLESHIPS_MAP_H

#include <SDL.h>
#include "Vector2D.h"

class Tile{
public:
    Tile();
    Tile(const char* path, int x, int y);
    ~Tile();
    void draw();
private:
    SDL_Texture* texture;
    SDL_Rect src, dest;
};

class Map {
private:
    Tile* grid[11][11];
    void init();
public:
    int margin = 32;
    int offset = 0;
    Map();
    Map(int offset);
    ~Map();
    void draw();
};


#endif //BATTLESHIPS_MAP_H
