#include "BattleshipAI.h"
#include <random>

void BattleshipAI::init() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            map[i][j] = {false, false};
        }
    }
}

void BattleshipAI::Shoot(Map &playerMap) {
    std::vector<TileAI> tileset;
    // Add points
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (map[i][j].first) {
                continue;
            }

            if (i + 1 < 10 && j + 1 < 10) {
                if (map[i + 1][j + 1].second) {
                    continue;
                }
            }
            if (i - 1 >= 0 && j + 1 < 10) {
                if (map[i - 1][j + 1].second) {
                    continue;
                }
            }
            if (i + 1 < 10 && j - 1 >= 0) {
                if (map[i + 1][j - 1].second) {
                    continue;
                }
            }
            if (i - 1 >= 0 && j - 1 >= 0) {
                if (map[i - 1][j - 1].second) {
                    continue;
                }
            }

            TileAI t;
            t.x = j;
            t.y = i;
            if (i - 1 >= 0) {
                if (map[i - 1][j].second) {
                    t += 5;
                }
            }

            if (j - 1 >= 0) {
                if (map[i][j - 1].second) {
                    t += 5;
                }
            }

            if (i + 1 < 10) {
                if (map[i + 1][j].second) {
                    t += 5;
                }
            }

            if (j + 1 < 10) {
                if (map[i][j - 1].second) {
                    t += 5;
                }
            }

            tileset.push_back(t);
        }
    }

    std::sort(tileset.begin(), tileset.end(), [](auto x, auto y) { return x > y; });

    if (!tileset.empty()) {
        if (tileset[0].value == 0) {
            // Pick on random (if not hit)
            std::random_device rd;
            std::mt19937 gen(rd());

            std::uniform_int_distribution<> dis(0, tileset.size() - 1);
            int index = dis(gen);
            int x = tileset[index].x;
            int y = tileset[index].y;

            map[y][x].second = playerMap.Shoot(x, y);
            map[y][x].first = true;
            return;

        }
    }

    if (tileset[0].value != 0) {
        map[tileset[0].y][tileset[0].x].second = playerMap.Shoot(tileset[0].x, tileset[0].y);
        map[tileset[0].y][tileset[0].x].first = true;
    }
}