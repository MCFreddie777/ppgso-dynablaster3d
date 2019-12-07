//
// Created by František Gič on 07/12/2019.
//
#pragma once

#ifndef DYNABLASTER3D_GAME_H
#define DYNABLASTER3D_GAME_H

#include "scene.h"

class Player;

class Game final : public Scene {
private:
    uint size = 15;
    float time = 0;

public:
    bool animate = true;
    
    unique_ptr<Level> level;
    Player *player;
    
    void init ();
    
    void update (float time) override;
    
    void handleKey (int key, int action) override;
    
};


#endif //DYNABLASTER3D_GAME_H
