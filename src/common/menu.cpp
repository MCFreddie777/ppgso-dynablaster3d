 //
// Created by František Gič on 07/12/2019.
//

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

#include "menu.h"

using namespace std;
using namespace glm;
using namespace ppgso;

// Static resources
unique_ptr<Shader> Menu::MenuObject::shader;

Menu::MenuObject::MenuObject (
    vec3 position, string texturePath, const string meshPath
) {
    this->position = position;
    this->rotation = {0, PI / 7, PI / 2};
    this->scale = {2.5, 2.5, 2.5};
    
    if (!shader) shader = make_unique<Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    
    if (!texture)
        texture = make_unique<Texture>(
            image::loadBMP("textures/"+ texturePath + ".bmp")
        );
    
    if (!mesh) mesh = make_unique<Mesh>("objects/" + meshPath + ".obj");
    
}

bool Menu::MenuObject::update (Scene &scene, float dt) {
    generateModelMatrix();
    return true;
}

void Menu::MenuObject::render (Scene &scene) {
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

void Menu::init () {
    Scene::init();
    
    auto
        controls = make_unique<Menu::MenuObject>(
        vec3{14, 9, 0},
        "white",
        "menu"
    );
    auto
        cursor = make_unique<Menu::MenuObject>(
        vec3{14, 13.0f, 0},
        "red",
        "cursor"
    );
    this->cursor = cursor.get();
    this->objects.push_back(move(cursor));
    this->objects.push_back(move(controls));
}

void Menu::update (float time) {
    Scene::update(time);
}

void Menu::handleKey (int key, int action) {
    if (action == GLFW_PRESS) {
        switch (key) {
            case (GLFW_KEY_ENTER): {
                if (this->cursor->position.y == 13.0f) {
                    this->windowRef->startGame();
                }
                else {
                    exit(0);
                }
                break;
            }
            case (GLFW_KEY_W): {
                this->cursor->position.y = 13.0f;
                break;
            }
            case (GLFW_KEY_S): {
                this->cursor->position.y = 8.75f;
                break;
            }
            default:
                break;
        }
    }
}