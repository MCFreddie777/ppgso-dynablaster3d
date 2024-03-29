//
// Created by František Gič on 30/11/2019.
//
#pragma once

#ifndef DYNABLASTER3D_ENEMY_H
#define DYNABLASTER3D_ENEMY_H

#include "../common/scene.h"
#include "../common/movement.h"
#include "../common/shadow.h"
#include "object.h"

class Enemy final : public Object {

private:
    bool hasMoved = false;
    float delay = 0.0f;
    int direction = 0;
    Shadow *shadow;
    
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Shader> shader;
    static std::unique_ptr<ppgso::Texture> texture;
    
    void roam (Scene &scene, float dt);

public:
    
    Enemy (vec3 position);
    
    bool update (Scene &scene, float dt) override;
    
    void render (Scene &scene) override;
    
};

#endif //DYNABLASTER3D_ENEMY_H



