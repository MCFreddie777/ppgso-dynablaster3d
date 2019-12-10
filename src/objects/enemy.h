//
// Created by František Gič on 30/11/2019.
//
#pragma once

#ifndef DYNABLASTER3D_ENEMY_H
#define DYNABLASTER3D_ENEMY_H

#include "../common/scene.h"
#include "../common/movement.h"
#include "object.h"

class Enemy final : public Object {

private:
    
    float delay = 0.0f;
    int direction = 0;
    
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Shader> shader;
    static std::unique_ptr<ppgso::Texture> texture;
    
    void roam (ComplexPosition complexPosition, float dt);

public:
    
    Enemy (vec3 position);
    
    bool update (Scene &scene, float dt) override;
    
    void render (Scene &scene) override;
    
};

#endif //DYNABLASTER3D_ENEMY_H



