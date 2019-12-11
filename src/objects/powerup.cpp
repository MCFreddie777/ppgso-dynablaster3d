//
// Created by František Gič on 30/11/2019.
//

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/transform.hpp>

#include "powerup.h"
#include "../common/movement.h"
#include "player.h"
#include "fire.h"

using namespace std;
using namespace glm;
using namespace ppgso;

// Static resources
unique_ptr<Shader> PowerUp::shader;
unique_ptr<Mesh> PowerUp::mesh;

PowerUp::PowerUp (vec3 position) {
    this->mode = "pickable";
    this->type = ((rand() % 2)) ? "bomb" : "fire";
    this->parent = nullptr;
    
    this->position = position;
    this->shadow = new Shadow(position, {scale.x - 1, 0.0f, scale.z - 1});
    
    if (!shader) shader = make_unique<Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture)
        texture = make_unique<Texture>(
            image::loadBMP("textures/powerup_" + type + ".bmp")
        );
    if (!mesh) mesh = make_unique<Mesh>("objects/powerup.obj");
}

PowerUp::PowerUp (string type, Scene &scene) {
    this->mode = "hover";
    this->shadow = nullptr;
    this->scale -= vec3{0.75, 0.75, 0};
    
    this->parent = dynamic_cast<Game &>(scene).player;
    
    if (!shader) shader = make_unique<Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture)
        texture = make_unique<Texture>(
            image::loadBMP("textures/powerup_" + type + ".bmp")
        );
    if (!mesh) mesh = make_unique<Mesh>("objects/powerup.obj");
}


bool PowerUp::update (Scene &scene, float dt) {
    age += dt;
    if (mode == "pickable") {
        // fall down if not hitting the ground
        if (position.y > 2) {
            position += (speed * dt);
            speed += speed * dt;
            shadow->scale += vec3{0.5 * dt, 0, 0.5 * dt};
        }
        else {
            if (position.y != 2) position.y = 2;
            shadow->update(position, scale, scene);
            speed = vec3{0, 0, 0};
        }
        rotation += momentum * dt;
        
        shadow->update(this->position, scene);
        shadow->update(scene, dt);
        shadow->render(scene);
        
        auto obj = Movement::getIntersectingObject(dynamic_cast<Game &>(scene), this);
        
        // If powerup is collected by the player
        if (dynamic_cast<Player *>(obj)) {
            auto player = dynamic_cast<Game &>(scene).player;
            
            if (this->type == "bomb") {
                player->bombs.modify("max", "increase");
                player->addPowerUp("bomb", scene);
            }
            else {
                player->bombs.modify("radius", "increase");
                player->addPowerUp("fire", scene);
            }
            return false;
        }
        // If powerup is being hit with fire, it burns down
        if (dynamic_cast<Fire *>(obj)) return false;
    }
    else {
        angle += dt;
        if (angle > 2 * PI) {
            angle = 0;
        }
        
        this->position = vec3{
            parent->position.x + cos(angle) * 0.5f,
            parent->position.y + 1.5f,
            parent->position.z + sin(angle) * 0.5f,
        };
        
        rotation += momentum * dt;
    }
    
    modelMatrix =
        translate(mat4(1.0f), position)
        * orientate4(rotation)
        * glm::scale(mat4(1.0f), scale);
    
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

