//
// Created by František Gič on 30/11/2019.
//

#ifndef DYNABLASTER3D_PLANE_H
#define DYNABLASTER3D_PLANE_H

#include "src/common/scene.h"
#include "object.h"

class Plane final : public Object {

private:
    
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Shader> shader;
    static std::unique_ptr<ppgso::Texture> texture;

public:
    
    Plane(uint size);
    
    bool update(Scene &scene, float dt) override;
    
    void render(Scene &scene) override;
    
};

#endif //DYNABLASTER3D_PLANE_H



