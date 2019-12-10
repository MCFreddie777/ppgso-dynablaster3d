//
// Created by František Gič on 04/12/2019.
//
#pragma once

#ifndef DYNABLASTER3D_FIRE_H
#define DYNABLASTER3D_FIRE_H

#include "../common/scene.h"
#include "object.h"


class Fire final : public Object {
private:
    
    float age{0.0f};
    float maxAge{2.5f};
    
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Shader> shader;
    static std::unique_ptr<ppgso::Texture> texture;
public:
    
    Fire (vec3 position, float rotation);
    
    bool update (Scene &scene, float dt) override;
    
    void render (Scene &scene) override;
};


#endif //DYNABLASTER3D_FIRE_H
