//
// Created by František Gič on 07/12/2019.
//
#pragma once

#ifndef DYNABLASTER3D_GAME_H
#define DYNABLASTER3D_GAME_H

#include "scene.h"

class Game final : public Scene {
private:
    uint size = 15;
public:
    
    bool animate = true;
    std::unique_ptr<Level> level;
    
    void init ();
    
    void update (float time) override;
};


#endif //DYNABLASTER3D_GAME_H
