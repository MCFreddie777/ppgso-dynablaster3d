//
// Created by František Gič on 04/12/2019.
//

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>
#include <src/common/movement.h>

#include "fire.h"

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
    Movement::getPossibleMove(dynamic_cast<Game &>(scene), this);
    
    age += dt;
    if (age > maxAge) {
        return false;
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