//
// Created by František Gič on 30/11/2019.
//

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

#include "plane.h"

using namespace std;
using namespace glm;
using namespace ppgso;

// Static resources
unique_ptr<Mesh> Plane::mesh;
unique_ptr<Texture> Plane::texture;
unique_ptr<Shader> Plane::shader;

Plane::Plane(uint size) {
    position = vec3{size*2-2, 0, size*2-2};
    
    // TODO: comment this when presenting
//    scale = scale * vec3{size, 1, size};
//    position = position -  vec3{size, 0, size} + vec3{1,0,1};

    if (!shader) shader = make_unique<Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture) texture = make_unique<Texture>(image::loadBMP("../resources/textures/grass.bmp"));
    if (!mesh) mesh = make_unique<Mesh>("../resources/objects/cube.obj");
}

bool Plane::update(Scene &scene, float dt) {
    generateModelMatrix();
    return true;
}

void Plane::render(Scene &scene) {
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

