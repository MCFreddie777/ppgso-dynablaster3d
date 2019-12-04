//
// Created by František Gič on 04/12/2019.
//

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

#include "bomb.h"

using namespace std;
using namespace glm;
using namespace ppgso;

// Static resources
unique_ptr<Mesh> Bomb::mesh;
unique_ptr<Texture> Bomb::texture;
unique_ptr<Shader> Bomb::shader;

Bomb::Bomb (vec3 position) {
    this->position = position;
    
    if (!shader) shader = make_unique<Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture) texture = make_unique<Texture>(image::loadBMP("../resources/textures/bomb.bmp"));
    if (!mesh) mesh = make_unique<Mesh>("../resources/objects/bomb.obj");
}

bool Bomb::update (Scene &scene, float dt) {
    generateModelMatrix();
    return true;
}

void Bomb::render (Scene &scene) {
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