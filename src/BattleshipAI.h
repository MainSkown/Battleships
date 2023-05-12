#ifndef BATTLESHIPS_BATTLESHIPAI_H
#define BATTLESHIPS_BATTLESHIPAI_H

#include <utility>
#include <iostream>
#include <vector>
#include "Map.h"
#include <algorithm>

struct TileAI{
    int value = 0;
    int x,y;

    int& operator +=(int x){
        return value +=x;
    }
    int& operator =(int x){
       return value = x;
    }
    bool operator >(TileAI& t){
        return value > t.value;
    }
    friend std::ostream& operator <<(std::ostream& o, TileAI& t ){
        o << " x: " << t.x << " y: " << t.y << " value: " << t.value;
        return o;
    }
};

class BattleshipAI {
private:
    std::pair<bool, bool> map[10][10];
public:
    void init();
    void Shoot(Map& playerMap);
};


#endif //BATTLESHIPS_BATTLESHIPAI_H
