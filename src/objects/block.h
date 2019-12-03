//
// Created by František Gič on 30/11/2019.
//

#ifndef DYNABLASTER3D_BLOCK_H
#define DYNABLASTER3D_BLOCK_H

#include "src/common/scene.h"
#include "object.h"

class Block final : public Object {

private:
    
    std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Shader> shader;
    std::unique_ptr<ppgso::Texture> texture;

public:
    Block(vec3 position, std::string type);
    
    bool update(Scene &scene, float dt) override;
    
    void render(Scene &scene) override;
};

#endif //DYNABLASTER3D_BLOCK_H



