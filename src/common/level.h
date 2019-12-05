//
// Created by František Gič on 30/11/2019.
//
#pragma once

#ifndef DYNABLASTER3D_LEVEL_H
#define DYNABLASTER3D_LEVEL_H

#include <vector>
#include <bin/ppgso/lib/ppgso.h>
#include <GLUT/glut.h>

using namespace std;
using namespace glm;

class Scene;

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
    
    vector<vector<char>> level;
    LevelObjects objects;
    
    void generate ();
    
    bool canSpawn (vec2 position, int radius);


public:
    uint size;
    uint blockCount = 0;
    
    Level (uint size);
    
    void create (Scene &scene);
    
    vector<vector<char>> get ();
};

#endif //DYNABLASTER3D_LEVEL_H
