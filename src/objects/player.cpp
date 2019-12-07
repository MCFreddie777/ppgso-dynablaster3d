//
// Created by František Gič on 30/11/2019.
//

#include <thread>
#include <chrono>
#include "src/common/scene.h"
#include "src/common/scenewindow.h"
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
    
    if (!shader) shader = make_unique<Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture)
        texture = make_unique<Texture>(image::loadBMP("../resources/textures/player.bmp"));
    if (!mesh) mesh = make_unique<Mesh>("../resources/objects/player.obj");
}

bool Player::update (Scene &scene, float dt) {
    ComplexPosition complexPosition = Movement::getPossibleMove(dynamic_cast<Game &>(scene), this);
    
    // Check if player intersects with enemy or fire
    auto obj = Movement::getIntersectingObject(dynamic_cast<Game &>(scene), this);
    
    // End of the game, pljeer is ded. NOOOOOOOOOOOO! Hulk sad.
    if (dynamic_cast<Enemy *>(obj) || dynamic_cast<Fire *>(obj)) {
        dynamic_cast<Game &>(scene).animate = false;
        this_thread::sleep_for(chrono::seconds(2));
        scene.windowRef->openMenu();
        return false;
    }
    
    handleMovement(scene.keyboard, dt, complexPosition, scene);
    generateModelMatrix();
    
    return true;
}

void Player::render (Scene &scene) {
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

void Player::handleMovement (
    map<int, int> keyboard, float dt, ComplexPosition complexPosition,
    Scene &scene
) {
    
    delay += dt;
    if (delay > 0.25f) {
        delay = 0;
    
        if (keyboard[GLFW_KEY_W] && complexPosition.move.up) {
            position.z += 2;
            rotation.z = 0;
        }
        if (keyboard[GLFW_KEY_S] && complexPosition.move.down) {
            position.z -= 2;
            rotation.z = -PI;
        }
        if (keyboard[GLFW_KEY_A] && complexPosition.move.left) {
            position.x += 2;
            rotation.z = PI / 2.0f;
        }
        if (keyboard[GLFW_KEY_D] && complexPosition.move.right) {
            position.x -= 2;
            rotation.z = -PI / 2.0f;
        }
        if (keyboard[GLFW_KEY_SPACE]) {
            if (this->bombs.number != this->bombs.max) {
                auto bomb = make_unique<Bomb>(position, *this);
                scene.objects.push_back(move(bomb));
                this->bombs.number++;
            }
        }
    }
}



