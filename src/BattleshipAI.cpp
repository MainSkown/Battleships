#include "BattleshipAI.h"

void BattleshipAI::init() {
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            map[i][j] = {false, false};
        }
    }
}

void BattleshipAI::Shoot(Map &playerMap) {
    std::vector<TileAI> tileset;
    // Add points
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            if(map[i][j].first){
                continue;
            }

            TileAI t;
            t.x = j;
            t.y = i;
            if(i - 1 >= 0){
                if(map[i - 1][j].second){
                    t += 5;
                }
                if(map[i - 1][j].first){
                    t += 2;
                }
            }

            if(j - 1 >= 0){
                if(map[i][j - 1].second){
                    t += 5;
                }
                if(map[i][j - 1].first){
                    t += 2;
                }
            }

            if(i + 1 < 10){
                if(map[i + 1][j].second){
                    t += 5;
                }
                if(map[i + 1][j].first){
                    t += 2;
                }
            }

            if(j + 1 < 10){
                if(map[i][j - 1].second){
                    t += 5;
                }
                if(map[i][j - 1].first){
                    t += 2;
                }
            }

            if(i + 1 < 10 && j + 1 < 10){
                if(map[i + 1][j + 1].second){
                    t = 0;
                }
            }
            if(i - 1 >= 0 && j + 1 < 10){
                if(map[i - 1][j + 1].second){
                    t = 0;
                }
            }
            if(i + 1 < 10 && j - 1 >= 0){
                if(map[i + 1][j + 1].second){
                    t = 0;
                }
            }
            if(i - 1 >= 0 && j - 1 >= 10){
                if(map[i + 1][j + 1].second){
                    t = 0;
                }
            }

            tileset.push_back(t);
        }
    }

    std::sort(tileset.begin(), tileset.end(), [](auto x, auto y) { return x > y; });

    map[tileset[0].y][tileset[0].x].second = playerMap.Shoot(tileset[0].x, tileset[0].y);
    map[tileset[0].y][tileset[0].x].first = true;
}