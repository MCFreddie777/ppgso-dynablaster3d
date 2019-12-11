//
// Created by František Gič on 30/11/2019.
//

#pragma once

#ifndef DYNABLASTER3D_POWERUP_H
#define DYNABLASTER3D_POWERUP_H

#include "../common/scene.h"
#include "../common/shadow.h"
#include "object.h"

using namespace ppgso;

class PowerUp final : public Object {

private:
    static unique_ptr<Shader> shader;
    static unique_ptr<Mesh> mesh;
    unique_ptr<Texture> texture;

public:
    string type;
    vec3 momentum = {0.0f, 0.0f, linearRand(-PI / 4.0f, PI / 4.0f)};
    vec3 speed = {0, -3.0f, 0};
    Shadow *shadow;
    
    PowerUp (vec3 position);
    
    bool update (Scene &scene, float dt) override;
    
    void render (Scene &scene) override;
};

#endif //DYNABLASTER3D_POWERUP_H



