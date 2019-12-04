//
// Created by František Gič on 04/12/2019.
//

#ifndef DYNABLASTER3D_BOMB_H
#define DYNABLASTER3D_BOMB_H

#include "src/common/scene.h"
#include "object.h"


class Bomb final : public Object {
private:
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Shader> shader;
    static std::unique_ptr<ppgso::Texture> texture;

public:
    
    Bomb (vec3 position);
    
    bool update (Scene &scene, float dt) override;
    
    void render (Scene &scene) override;
};


#endif //DYNABLASTER3D_BOMB_H
