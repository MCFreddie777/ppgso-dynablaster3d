//
// Created by František Gič on 04/12/2019.
//
#pragma once

#ifndef DYNABLASTER3D_BOMB_H
#define DYNABLASTER3D_BOMB_H

#include "src/common/scene.h"
#include "object.h"
#include "player.h"


class Bomb final : public Object {
private:
    
    float age{0.0f};
    float maxAge{3.5f};
    Player *player;
    
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Shader> shader;
    static std::unique_ptr<ppgso::Texture> texture;
    
    void explode (Scene &scene, uint radius);

public:
    
    Bomb (vec3 position, Player &player);
    
    bool update (Scene &scene, float dt) override;
    
    void render (Scene &scene) override;
};


#endif //DYNABLASTER3D_BOMB_H
