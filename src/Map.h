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
    void SetTexture(const char* path);
private:
    SDL_Texture* texture;
    SDL_Rect src{}, dest{};
};

class Map {
private:
    const int shipNumber = 35;
    void init();
public:
    Tile* grid[11][11];
    // first - isHit, second - does have ship
    std::pair<bool, bool> ships[10][10];

    int margin = 32;
    int offset = 0;
    bool isPlayer = false;
    bool confirmed = false;
    Map();
    Map(int offset);
    ~Map();
    void draw();
    void update();
    void PickGrid(int xIndex, int yIndex);
    bool confirm();
};


#endif //BATTLESHIPS_MAP_H
