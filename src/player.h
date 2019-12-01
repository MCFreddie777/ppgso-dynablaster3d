//
// Created by František Gič on 30/11/2019.
//

#ifndef DYNABLASTER3D_PLAYER_H
#define DYNABLASTER3D_PLAYER_H

#include "scene.h"
#include "objects/object.h"

class Player final : public Object {

private:
    
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Shader> shader;
    static std::unique_ptr<ppgso::Texture> texture;

public:
    
    Player(vec3 position);
    
    bool update(Scene &scene, float dt) override;
    
    void render(Scene &scene) override;
    
};

#endif //DYNABLASTER3D_PLAYER_H



