//
// Created by František Gič on 30/11/2019.
//

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

#include "block.h"

using namespace std;
using namespace glm;
using namespace ppgso;

// Static resources
unique_ptr<Shader> Block::shader;

Block::Block (vec3 position, string type) {
    this->position = position;
    
    if (!shader) shader = make_unique<Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture)
        texture = make_unique<Texture>(image::loadBMP("../resources/textures/" + type + ".bmp"));
    if (!mesh) mesh = make_unique<Mesh>("../resources/objects/cube.obj");
}

bool Block::update (Scene &scene, float dt) {
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

