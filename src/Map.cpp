#include "Map.h"
#include "TextureManager.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

const char *tilePath = "assets/tile.png";
const char *selectedPath = "assets/selectedTile.png";

/* Tile class */
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

void Tile::SetTexture(const char *path) {
    texture = TextureManager::LoadTexture(path);
}

/* Map class */
void Map::init() {
    grid[0][0] = new Tile("assets/empty.png", 0, 0);
    char c = 'A';
    // Add letters and numbers
    for (int i = 1; i < 11; i++) {
        std::string tS(1, c);
        grid[i][0] = new Tile(("assets/" + std::to_string(i) + ".png").c_str(), offset + margin, margin + i * 32);
        grid[0][i] = new Tile(("assets/" + tS + ".png").c_str(), offset + margin + i * 32, margin);
        c += 1;
    }

    // Inside tiles
    for (int i = 1; i < 11; i++) {
        for (int j = 1; j < 11; j++) {
            grid[i][j] = new Tile(tilePath, offset + margin + i * 32, margin + j * 32);
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
    for (int i = 0; i < 11; i++) {
        for (auto &j: grid) {
            delete j[i];
        }
    }
}

void Map::draw() {
    for (auto &i: grid) {
        for (auto &j: i) {
            j->draw();
        }
    }
}

void Map::PickGrid(int x, int y) {
    if (isPlayer) {
        // Return if game is in after picking faze
        if (confirmed) return;
        // Pick grid
        int xIndex = floor((x - margin - offset) / 32);
        int yIndex = floor((y - margin) / 32);
        std::cout << xIndex << " " << yIndex << std::endl;
        // Player clicked outside the map
        if (xIndex < 1 || yIndex < 1 || xIndex > 10 || yIndex > 10) return;

        if (!ships[xIndex - 1][yIndex - 1].second) {
            // Ship was not picked
            ships[xIndex - 1][yIndex - 1] = {false, true};
            grid[xIndex][yIndex]->SetTexture(selectedPath);
        } else {
            // Ship was picked -> unpicking
            ships[xIndex - 1][yIndex - 1] = {false, false};
            grid[xIndex][yIndex]->SetTexture(tilePath);
        }

    } else {
        // Enemy map -> attacking tiles
    }
}

void Map::update() {
    std::vector<std::pair<bool, bool>> _shipVec;

    // Counting hit ships
    for (auto &ship: ships) {
        for (const auto &j: ship) {
            _shipVec.push_back(j);
        }
    }

    // Check if all ships are hit
    if (shipNumber ==
        std::count_if(_shipVec.begin(), _shipVec.end(), [](std::pair<bool, bool> x) { return x.first && x.second; })) {
        // If true this map has lost
        GameEngine::MapLost(this);
    }
}

/* Rules
 * 5x []
 * 4x [][]
 * 3x [][][]
 * 2x [][][][]
 * 1x [][][][][]
 * Can not touch
 * Can not bend
*/

bool Map::confirm() {
    std::vector<std::pair<bool, bool>> _shipVec;

    // Counting hit ships
    for (auto &ship: ships) {
        for (const auto &j: ship) {
            _shipVec.push_back(j);
        }
    }

    // Count how many ships there are
    int numberOfPickedShips = std::count_if(_shipVec.begin(), _shipVec.end(),
                                            [](std::pair<bool, bool> x) { return x.second; });
    if (numberOfPickedShips > shipNumber) {
        // There are too many ships
        std::cout << "Too many ships" << std::endl;
        return false;
    }

    int ship1xCount = 0;
    int ship2xCount = 0;
    int ship3xCount = 0;
    int ship4xCount = 0;
    int ship5xCount = 0;

    // Count number of ships
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (ships[i][j].second) {
                bool north = false, east = false, west = false, south = false, doubleNorth = false, doubleEast = false, doubleWest = false, doubleSouth = false
                , tripleNorth = false, tripleWest = false;
                if (i + 1 < 10) {
                    south = ships[i + 1][j].second;
                }
                if (i - 1 >= 0) {
                    north = ships[i - 1][j].second;
                }
                if (j + 1 < 10) {
                    east = ships[i][j + 1].second;
                }
                if (j - 1 >= 0) {
                    west = ships[i][j - 1].second;
                }
                if (i + 2 < 10) {
                    doubleSouth = ships[i + 2][j].second;
                }
                if (i - 2 >= 0) {
                    doubleNorth = ships[i - 2][j].second;
                }
                if (j + 2 < 10) {
                    doubleEast = ships[i][j + 2].second;
                }
                if (j - 2 >= 0) {
                    doubleWest = ships[i][j - 2].second;
                }
                if (i - 3 >= 0) {
                    tripleNorth = ships[i - 3][j].second;
                }
                if (j - 3 >= 0) {
                    tripleWest = ships[i][j - 3].second;
                }

                if ((north && west) || (north && east) || (south && west) || (south && east)) {
                    // There is a bend
                    std::cout << "There is a bend\n";
                    std::cout << "North: " << north << " East: " << east << " West: " << west << " South: " << south
                              << "\n";
                    return false;
                }

                if (!north && !east && !west && !south) {
                    // There is a 1x ship
                    ship1xCount++;
                }
                if ((!north && south && !doubleSouth) || (!west && east && !doubleEast)) {
                    // There is a 2x ship
                    ship2xCount++;
                }
                if ((north && south && !doubleNorth && !doubleSouth) || (east && west && !doubleEast && !doubleWest)) {
                    // There is a 3x ship
                    ship3xCount++;
                }
                if ((doubleNorth && north && south && !doubleSouth && !tripleNorth) ||
                    (doubleWest && west && east && !doubleEast && !tripleWest)) {
                    // There is a 4x ship
                    ship4xCount++;
                }
                if ((doubleNorth && north && south && doubleSouth) || (doubleWest && west && east && doubleEast)) {
                    // There is a 5x ship
                    ship5xCount++;
                }
                if (i + 1 < 10 && j + 1 < 10) {
                    if (ships[i + 1][j + 1].second) {
                        // There is a corner
                        return false;
                    }
                }
                if (i + 1 < 10 && j - 1 >= 0) {
                    if (ships[i + 1][j - 1].second) {
                        // There is a corner
                        return false;
                    }
                }
                if (i - 1 >= 0 && j + 1 < 10) {
                    if (ships[i - 1][j + 1].second) {
                        // There is a corner
                        return false;
                    }
                }
                if (i - 1 >= 0 && j - 1 >= 0) {
                    if (ships[i - 1][j - 1].second) {
                        // There is a corner
                        return false;
                    }
                }
            }
        }
    }

    if (ship1xCount != 5 || ship2xCount != 4 || ship3xCount != 3 || ship4xCount != 2 || ship5xCount != 1) {
        // Wrong number of ships
        std::cout << "Wrong number of ships\n";
        std::cout << "1x: " << ship1xCount << " 2x: " << ship2xCount << " 3x: " << ship3xCount << " 4x: " << ship4xCount
                  << " 5x: " << ship5xCount << "\n";
        return false;
    }

    confirmed = true;
    return true;
}