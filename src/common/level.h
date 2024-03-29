//
// Created by František Gič on 30/11/2019.
//
#pragma once

#ifndef DYNABLASTER3D_LEVEL_H
#define DYNABLASTER3D_LEVEL_H

#include <vector>
#include <bin/ppgso/lib/ppgso.h>
#include <GL/glew.h>

using namespace std;
using namespace glm;

class Scene;

class Game;

enum ObjectType {
    PLAYER = 'P',
    ENEMY = 'E',
    WALL = 'W',
    BLOCK = 'B',
    FIRE = 'F'
};

typedef struct ObjectCounter {
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
    
    void dropPowerUp (Game &game);
};

#endif //DYNABLASTER3D_LEVEL_H
