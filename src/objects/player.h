//
// Created by František Gič on 30/11/2019.
//

#ifndef DYNABLASTER3D_PLAYER_H
#define DYNABLASTER3D_PLAYER_H

#include "src/common/scene.h"
#include "src/common/movement.h"
#include "object.h"

class Player final : public Object {

private:
    
    float delay = 0.0f;
    
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Shader> shader;
    static std::unique_ptr<ppgso::Texture> texture;
    
    void handleMovement (
        map<int, int> keyboard, float dt, ComplexPosition complexPosition, Scene
    &scene
    );

public:
    
    Player (vec3 position);
    
    bool update (Scene &scene, float dt) override;
    
    void render (Scene &scene) override;
};

#endif //DYNABLASTER3D_PLAYER_H



