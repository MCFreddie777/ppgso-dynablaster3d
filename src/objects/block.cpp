//
// Created by František Gič on 30/11/2019.
//

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

#include "block.h"
#include "src/common/movement.h"
#include "fire.h"

using namespace std;
using namespace glm;
using namespace ppgso;

// Static resources
unique_ptr<Shader> Block::shader;

Block::Block (vec3 position, const string texturePath, const string meshPath) {
    this->position = position;
    this->type = texturePath; // wall | block
    
    if (!shader) shader = make_unique<Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture)
        texture = make_unique<Texture>(image::loadBMP("../resources/textures/" + texturePath + ""
                                                                                               ".bmp"));
    if (!mesh) mesh = make_unique<Mesh>("../resources/objects/" + meshPath + ".obj");
}

bool Block::update (Scene &scene, float dt) {
    auto obj = Movement::getIntersectingObject(dynamic_cast<Game &>(scene), this);
    
    // If fire meets the block, it is removed from the scene
    if (dynamic_cast<Fire *>(obj) && this->type == "block")
        return false;
    
    generateModelMatrix();
    return true;
}

void Block::render (Scene &scene) {
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

