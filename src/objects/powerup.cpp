//
// Created by František Gič on 30/11/2019.
//

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

#include "powerup.h"
#include "src/common/movement.h"
#include "player.h"
#include "fire.h"

using namespace std;
using namespace glm;
using namespace ppgso;

// Static resources
unique_ptr<Shader> PowerUp::shader;
unique_ptr<Mesh> PowerUp::mesh;

PowerUp::PowerUp (vec3 position) {
    this->type = ((rand() % 2)) ? "bomb" : "fire";
    
    this->position = position;
    if (!shader) shader = make_unique<Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture)
        texture = make_unique<Texture>(
            image::loadBMP("../resources/textures/powerup_" + type + ".bmp")
        );
    if (!mesh) mesh = make_unique<Mesh>("../resources/objects/powerup.obj");
}

bool PowerUp::update (Scene &scene, float dt) {
    
    // fall down if not hitting the ground
    if (position.y > 2) {
        position += (speed * dt);
        speed += speed * dt;
    }
    else
        speed = vec3{0, 0, 0};
    
    rotation += momentum * dt;
    
    auto obj = Movement::getIntersectingObject(dynamic_cast<Game &>(scene), this);
    
    // If powerup is collected by the player
    if (dynamic_cast<Player *>(obj)) {
        if (this->type == "bomb") {
            dynamic_cast<Game &>(scene).player->bombs.max++;
        }
        else {
            dynamic_cast<Game &>(scene).player->bombs.radius++;
        }
        return false;
    }
    // If powerup is being hit with fire
    if (dynamic_cast<Fire *>(obj)) return false;
    
    generateModelMatrix();
    return true;
}

void PowerUp::render (Scene &scene) {
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

