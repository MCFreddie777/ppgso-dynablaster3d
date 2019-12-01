//
// Created by František Gič on 30/11/2019.
//

#ifndef DYNABLASTER3D_LEVEL_H
#define DYNABLASTER3D_LEVEL_H

#include <vector>

#include "src/scene.h"

using namespace std;

typedef struct ObjectCounter {
    double spawnRate;
    int maxNumber;
    int number;
};

typedef struct LevelObjects {
    ObjectCounter enemies;
    ObjectCounter player;
    ObjectCounter blocks;
};

class Level {

private:
    
    uint size;
    vector<vector<char>> level;
    LevelObjects objects;
    
    void generate();

public:
    
    explicit Level(uint size);
    
    void create(Scene &scene);
    
};

#endif //DYNABLASTER3D_LEVEL_H
