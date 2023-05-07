#include "Map.h"
#include "TextureManager.h"
#include <string>
#include <iostream>

Tile::Tile(const char *path, int x, int y) {
    this->texture = TextureManager::LoadTexture(path);
    src.w = src.h = dest.h = dest.w = 32;
    src.x = src.y = 0;
    dest.x = x;
    dest.y = y;
}

Tile::~Tile() {
    SDL_DestroyTexture(texture);
}

void Tile::draw() {
    TextureManager::Draw(texture, src, dest);
}

void Map::init() {
    grid[0][0] = new Tile("assets/empty.png", 0,0);
    char c = 'A';
    // Add letters and numbers
    for(int i = 1; i < 11; i++){
        std::string tS(1, c);
        grid[i][0] = new Tile(("assets/" + std::to_string(i) + ".png").c_str(), offset + margin, margin + i * 32);
        grid[0][i] = new Tile(("assets/" + tS + ".png").c_str(), offset + margin + i * 32, margin);
        c+= 1;
    }

    // Inside tiles
    for(int i = 1; i < 11; i++){
        for(int j = 1; j < 11; j++){
            grid[i][j] = new Tile("assets/tile.png", offset + margin + i * 32, margin + j * 32);
        }
    }
}

Map::Map() {
    init();
}

Map::Map(int offset) {
    this->offset = offset;
    init();
}

Map::~Map() {
    for(int i = 0; i < 11; i++){
        for(int j = 0; j < 11; j++){
            delete grid[j][i];
        }
    }
}

void Map::draw() {
    for(int i = 0; i < 11; i++){
        for(int j = 0; j < 11; j++){
            if(grid != nullptr) {
                grid[i][j]->draw();
            }
        }
    }
}