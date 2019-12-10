//
// Created by František Gič on 30/11/2019.
//

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

#include "enemy.h"
#include "fire.h"

using namespace std;
using namespace glm;
using namespace ppgso;

// Static resources
unique_ptr<Mesh> Enemy::mesh;
unique_ptr<Texture> Enemy::texture;
unique_ptr<Shader> Enemy::shader;

Enemy::Enemy (vec3 position) {
    this->position = position;
    
    if (!shader) shader = make_unique<Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture) texture = make_unique<Texture>(image::loadBMP("textures/enemy.bmp"));
    if (!mesh) mesh = make_unique<Mesh>("objects/enemy.obj");
}

bool Enemy::update (Scene &scene, float dt) {
    ComplexPosition complexPosition = Movement::getPossibleMove(dynamic_cast<Game &>(scene), this);
    
    // Check if enemy intersects with fire
    auto obj = Movement::getIntersectingObject(dynamic_cast<Game &>(scene), this);
    
    if (dynamic_cast<Fire *>(obj)) {
        return false;
    }
    
    if (dynamic_cast<Game &>(scene).animate) roam(complexPosition, dt);
    generateModelMatrix();
    return true;
}

void Enemy::roam (ComplexPosition complexPosition, float dt) {
    delay += dt;
    
    if (delay > 0.3f) {
        delay = 0;
        
        // generate new direction when on crossroads or corners
        if (complexPosition.inCorner || complexPosition.inCrossRoads)
            direction = 0;
        
        // generate new direction
        if (!direction) {
            // if there are more ways to go
            if (complexPosition.move.up + complexPosition.move.down + complexPosition.move.left +
                complexPosition.move.right > 1) {
                direction = rand() % 4 + 1;
            }
                // else go the only way possible
            else {
                if (complexPosition.move.up) direction = 1;
                if (complexPosition.move.down) direction = 2;
                if (complexPosition.move.left) direction = 3;
                if (complexPosition.move.right) direction = 4;
            }
        }
        
        switch (direction) {
            case 1: {
                if (complexPosition.move.up) {
                    position.z += 2;
                    rotation.z = 0;
                }
                else {
                    direction = 0;
                }
                break;
            }
            case 2: {
                if (complexPosition.move.down) {
                    position.z -= 2;
                    rotation.z = -PI;
                }
                else {
                    direction = 0;
                }
                break;
            }
            case 3: {
                if (complexPosition.move.left) {
                    position.x += 2;
                    rotation.z = PI / 2.0f;
                }
                else {
                    direction = 0;
                }
                break;
            }
            case 4: {
                if (complexPosition.move.right) {
                    position.x -= 2;
                    rotation.z = -PI / 2.0f;
                }
                else {
                    direction = 0;
                }
                break;
            }
            default:
                break;
        }
    }
}

void Enemy::render (Scene &scene) {
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

