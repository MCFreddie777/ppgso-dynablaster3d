//
// Created by František Gič on 04/12/2019.
//
#pragma once

#ifndef DYNABLASTER3D_BOMB_H
#define DYNABLASTER3D_BOMB_H

#include "../common/game.h"
#include "../common/shadow.h"
#include "object.h"

class Player;

class Bomb final : public Object {
private:
    
    float age{0.0f};
    float maxAge{3.5f};
    float currScale{0.0f};
    Player *player;
    Shadow *shadow;
    
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Shader> shader;
    static std::unique_ptr<ppgso::Texture> texture;
    
    void explode (Game &scene, uint radius);

public:
    
    Bomb (vec3 position, Player &player);
    
    bool update (Scene &scene, float dt) override;
    
    void render (Scene &scene) override;
};


#endif //DYNABLASTER3D_BOMB_H
