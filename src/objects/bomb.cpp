//
// Created by František Gič on 04/12/2019.
//

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>
#include "../common/movement.h"

#include "bomb.h"
#include "player.h"
#include "fire.h"

using namespace std;
using namespace glm;
using namespace ppgso;

// Static resources
unique_ptr<Mesh> Bomb::mesh;
unique_ptr<Texture> Bomb::texture;
unique_ptr<Shader> Bomb::shader;

Bomb::Bomb (vec3 position, Player &player) {
    this->position = position;
    this->player = &player;
    this->shadow = new Shadow(position, this->scale);
    
    if (!shader) shader = make_unique<Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture) texture = make_unique<Texture>(image::loadBMP("textures/bomb.bmp"));
    if (!mesh) mesh = make_unique<Mesh>("objects/bomb.obj");
}

bool Bomb::update (Scene &scene, float dt) {
    age += dt;
    
    // Pulsing bomb
    if (currScale == 0.0f)
        currScale = dt;
    if (this->scale.y > 1.5f)
        currScale = -dt * age;
    if (this->scale.y < 1.0f)
        currScale = dt * age;
    this->scale += currScale;
    
    shadow->update(this->position, this->scale, scene);
    shadow->update(scene, dt);
    shadow->render(scene);
    
    if (age > maxAge) {
        explode(dynamic_cast<Game &>(scene), player->bombs.radius);
        return false;
    }
    
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

void Bomb::explode (Game &scene, uint radius) {
    this->player->bombs.number--;
    
    // Create fire element (radius) blocks from the bomb position
    for (
        uint i = ((uint) position.x) / 2 - radius;
        i <= ((uint) position.x) / 2 + radius;
        i++) {
        
        for (
            uint j = ((uint) position.z) / 2 - radius;
            j <= ((uint) position.z) / 2 + radius;
            j++) {
            
            // Check for level boundaries and walls
            if (
                (i == ((uint) position.x) / 2 || j == ((uint) position.z) / 2) &&
                i > 0 &&
                j > 0 &&
                ((uint) i) < scene.level->size &&
                ((uint) j) < scene.level->size &&
                (scene.level->get()[i][j] != ObjectType::WALL)
                ) {
                
                float fireRot = (i == ((uint) position.x) / 2) ? (PI / 2.0f) : 0;
                auto fire = make_unique<Fire>(vec3{i * 2, position.y, j * 2}, fireRot);
                scene.objects.push_back(move(fire));
                
                // Second fire is being generated on the position of bomb with rotation of 90
                // degrees to create the X effect
                if (i == ((uint) position.x) / 2 && j == ((uint) position.z) / 2) {
                    auto fire = make_unique<Fire>(vec3{i * 2, position.y, j * 2}, 0);
                    scene.objects.push_back(move(fire));
                }
            }
        }
    }
}
