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
    this->nextKeyPos = position;
    this->shadow = new Shadow(position, this->scale);
    
    if (!shader) shader = make_unique<Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture) texture = make_unique<Texture>(image::loadBMP("textures/enemy.bmp"));
    if (!mesh) mesh = make_unique<Mesh>("objects/enemy.obj");
}

bool Enemy::update (Scene &scene, float dt) {
    if (hasMoved) {
        position = lerp(position, nextKeyPos, dt * 6);
        if (abs(nextKeyPos.z - position.z) < 0.2f && abs(nextKeyPos.x - position.x) < 0.2f) {
            position = nextKeyPos;
            hasMoved = false;
        }
    }
    
    shadow->update(this->position, scene);
    shadow->update(scene, dt);
    shadow->render(scene);
    
    if (dynamic_cast<Game &>(scene).animate) roam(scene, dt);
    
    // Check if enemy intersects with fire
    auto obj = Movement::getIntersectingObject(dynamic_cast<Game &>(scene), this);
    
    if (dynamic_cast<Fire *>(obj)) {
        return false;
    }
    
    generateModelMatrix();
    return true;
}

void Enemy::roam (Scene &scene, float dt) {
    delay += dt;
    
    if (delay > 0.5f) {
        delay = 0;
        
        ComplexPosition complexPosition =
            Movement::getPossibleMove(dynamic_cast<Game &>(scene), this);
        
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
        
        this->hasMoved = true;
        switch (direction) {
            case 1: {
                if (complexPosition.move.up) {
                    this->nextKeyPos = vec3{position.x, position.y, position.z + 2};
                    rotation.z = 0;
                }
                else {
                    direction = 0;
                }
                break;
            }
            case 2: {
                if (complexPosition.move.down) {
                    this->nextKeyPos = vec3{position.x, position.y, position.z - 2};
                    rotation.z = -PI;
                }
                else {
                    direction = 0;
                }
                break;
            }
            case 3: {
                if (complexPosition.move.left) {
                    this->nextKeyPos = vec3{position.x + 2, position.y, position.z};
                    rotation.z = PI / 2.0f;
                }
                else {
                    direction = 0;
                }
                break;
            }
            case 4: {
                if (complexPosition.move.right) {
                    this->nextKeyPos = vec3{position.x - 2, position.y, position.z};
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

