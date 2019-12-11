//
// Created by František Gič on 30/11/2019.
//
#pragma once

#ifndef DYNABLASTER3D_PLAYER_H
#define DYNABLASTER3D_PLAYER_H

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

#include "../common/movement.h"
#include "../common/shadow.h"
#include "object.h"
#include "block.h"

class Bomb;

class BombInfo {

public:
    uint number = 0;
    uint max;
    uint radius = 1;
    
    BombInfo (uint maxBombs) {
        this->max = 1;
    }
};

class Player final : public Object {

private:
    bool hasMoved = false;
    float delay = 0.0f;
    Shadow *shadow;
    
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Shader> shader;
    static std::unique_ptr<ppgso::Texture> texture;
    
    void handleMovement (map<int, int> keyboard, float dt, Scene &scene);

public:
    
    short direction = 0;
    
    BombInfo bombs = BombInfo(1u);
    
    explicit Player (vec3 position);
    
    bool update (Scene &scene, float dt) override;
    
    void render (Scene &scene) override;
};

#endif //DYNABLASTER3D_PLAYER_H



