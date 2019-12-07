//
// Created by František Gič on 04/12/2019.
//

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>
#include <src/common/movement.h>

#include "fire.h"
#include "block.h"

using namespace std;
using namespace glm;
using namespace ppgso;

// Static resources
unique_ptr<Mesh> Fire::mesh;
unique_ptr<Texture> Fire::texture;
unique_ptr<Shader> Fire::shader;

Fire::Fire (vec3 position, float rotation) {
    this->position = position;
    this->rotation.z = rotation;
    
    if (!shader) shader = make_unique<Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture)
        texture = make_unique<Texture>(image::loadBMP("../resources/textures/fire.bmp"));
    if (!mesh)
        mesh = make_unique<Mesh>("../resources/objects/fire.obj");
}

bool Fire::update (Scene &scene, float dt) {
    age += dt;
    if (age > maxAge) {
        return false;
    }
    
    auto obj = Movement::getIntersectingObject(dynamic_cast<Game &>(scene), this);
    
    // If fire meets the destroyable block, block is removed from the scene
    if (
        dynamic_cast<Block *>(obj) &&
        (dynamic_cast<Block *>(obj))->type == "block"
        ) {
        
        auto i = std::begin(scene.objects);
        while (i != std::end(scene.objects)) {
            
            unique_ptr<Object> &object = *i;
            
            if (object.get() == obj) {
                i = scene.objects.erase(i);
                dynamic_cast<Game &>(scene).level->blockCount--;
            }
            else {
                i++;
            }
            continue;
        }
    }
    
    generateModelMatrix();
    return true;
}

void Fire::render (Scene &scene) {
    shader->use();
    
    // Set up light
    shader->setUniform("LightDirection", scene.lightDirection);
    shader->setUniform("LightColor", scene.lightColor);
    
    // use camera
    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);
    
    // render mesh
    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("Texture", *texture);
    
    mesh->render();
}