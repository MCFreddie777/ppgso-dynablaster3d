//
// Created by František Gič on 30/11/2019.
//

#include <thread>
#include <chrono>
#include "../common/scene.h"
#include "../common/scenewindow.h"
#include "player.h"
#include "enemy.h"
#include "bomb.h"
#include "fire.h"

using namespace std;
using namespace glm;
using namespace ppgso;

// Static resources
unique_ptr<Mesh> Player::mesh;
unique_ptr<Texture> Player::texture;
unique_ptr<Shader> Player::shader;

Player::Player (vec3 position) {
    this->position = position;
    this->nextKeyPos = position;
    
    if (!shader) shader = make_unique<Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture)
        texture = make_unique<Texture>(image::loadBMP("textures/player.bmp"));
    if (!mesh) mesh = make_unique<Mesh>("objects/player.obj");
}

bool Player::update (Scene &scene, float dt) {
    
    if (hasMoved) {
        position = lerp(position, nextKeyPos, dt * 6);
        if (abs(nextKeyPos.z - position.z) < 0.1f && abs(nextKeyPos.x - position.x) < 0.1f) {
            position = nextKeyPos;
            hasMoved = false;
        }
    }
    
    // Check if player intersects with enemy or fire
    auto obj = Movement::getIntersectingObject(dynamic_cast<Game &>(scene), this);
    
    // End of the game, pljeer is ded. NOOOOOOOOOOOO! Hulk sad.
    if (dynamic_cast<Enemy *>(obj) || dynamic_cast<Fire *>(obj)) {
        dynamic_cast<Game &>(scene).animate = false;
        this_thread::sleep_for(chrono::seconds(2));
        scene.windowRef->openMenu();
        return false;
    }
    
    handleMovement(scene.keyboard, dt, scene);
    generateModelMatrix();
    return true;
}

void Player::render (Scene &scene) {
    shader->use();
    
    // Set up light
    shader->setUniform("LightDirection", scene.lightDirection);
//    shader->setUniform("LightDirection2", scene.lightDirection2);
    
    shader->setUniform("LightColor", scene.lightColor);
//    shader->setUniform("LightColor2", scene.lightColor2);
    
    // use camera
    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);
    
    // render mesh
    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("Texture", *texture);
    
    mesh->render();
}

void Player::handleMovement (map<int, int> keyboard, float dt, Scene &scene) {
    // key event throttling
    delay += dt;
    
    if (
        (
            (
                keyboard[GLFW_KEY_W] || keyboard[GLFW_KEY_A] ||
                keyboard[GLFW_KEY_S] || keyboard[GLFW_KEY_D]
            ) &&
            (position.z == nextKeyPos.z && position.x == nextKeyPos.x)
        )
        
        ) {
        ComplexPosition complexPosition =
            Movement::getPossibleMove(dynamic_cast<Game &> (scene), this);
        
        if (Movement::canMove(complexPosition) && !scene.camera->isFirstPersonMode()) {
            this->hasMoved = true;
            
            if (keyboard[GLFW_KEY_W] && complexPosition.move.up) {
                this->nextKeyPos = vec3{position.x, position.y, position.z + 2};
                direction = 0;
                rotation.z = 0;
            }
            if (keyboard[GLFW_KEY_S] && complexPosition.move.down) {
                this->nextKeyPos = vec3{position.x, position.y, position.z - 2};
                direction = 2;
                rotation.z = -PI;
            }
            if (keyboard[GLFW_KEY_A] && complexPosition.move.left) {
                this->nextKeyPos = vec3{position.x + 2, position.y, position.z};
                direction = 3;
                rotation.z = PI / 2.0f;
            }
            if (keyboard[GLFW_KEY_D] && complexPosition.move.right) {
                this->nextKeyPos = vec3{position.x - 2, position.y, position.z};
                direction = 1;
                rotation.z = -PI / 2.0f;
            }
        }
        else if (scene.camera->isFirstPersonMode()) {
            this->hasMoved = true;
            
            if (keyboard[GLFW_KEY_W] && Movement::canMove(complexPosition)) {
                switch (direction) {
                    case 0: {
                        if (complexPosition.move.up)
                            this->nextKeyPos = vec3{position.x, position.y, position.z + 2};
                        break;
                    }
                    case 1: {
                        if (complexPosition.move.right)
                            this->nextKeyPos = vec3{position.x - 2, position.y, position.z};
                        break;
                    }
                    case 2: {
                        if (complexPosition.move.down)
                            this->nextKeyPos = vec3{position.x, position.y, position.z - 2};
                        break;
                    }
                    case 3: {
                        if (complexPosition.move.left)
                            this->nextKeyPos = vec3{position.x + 2, position.y, position.z};
                        break;
                    }
                }
            }
            // THrottling rotation events
            if (delay > 0.25f) {
                delay = 0;
                if (keyboard[GLFW_KEY_S]) {
                    rotation.z += PI;
                    if (direction == 0 || direction == 1)
                        direction += 2;
                    else direction -= 2;
                }
                if (keyboard[GLFW_KEY_A]) {
                    rotation.z += PI / 2;
                    if (direction != 0)
                        direction -= 1;
                    else direction = 3;
                }
                if (keyboard[GLFW_KEY_D]) {
                    rotation.z -= PI / 2;
                    if (direction != 3)
                        direction += 1;
                    else direction = 0;
                }
            }
            scene.camera->updateWithDirection(position, direction);
        }
    }
    
    if (keyboard[GLFW_KEY_SPACE]) {
        if (this->bombs.number != this->bombs.max) {
            auto obj = Movement::getIntersectingObject(dynamic_cast<Game &>(scene), position);
            if (!obj || dynamic_cast<Player *>(obj)) {
                auto bomb = make_unique<Bomb>(position, *this);
                scene.objects.push_back(move(bomb));
                this->bombs.number++;
            }
        }
    }
}


