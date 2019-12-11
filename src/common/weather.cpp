//
// Created by František Gič on 11/12/2019.
//
#include <random>
#include "weather.h"
#include "game.h"

using namespace std;

// Static resources
unique_ptr<Shader> Weather::RainParticle::shader;
unique_ptr<Mesh> Weather::RainParticle::mesh;
unique_ptr<Texture> Weather::RainParticle::texture;

Weather::RainParticle::RainParticle (vec3 position, Weather *parent) {
    this->position = position;
    this->scale = vec3{.05f, .3f, .05f};
    this->parent = parent;
    
    if (!shader) shader = make_unique<Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture) texture = make_unique<Texture>(image::loadBMP("textures/blau.bmp"));
    if (!mesh) mesh = make_unique<Mesh>("objects/cube.obj");
    
}

bool Weather::RainParticle::update (Scene &scene, float dt) {
    if (position.y <= 1)
        return false;
    else if (position.y > 1) {
        position += vec3{(speed.x * dt) + parent->wind, speed.y * dt, speed.z * dt};
        speed += speed * dt;
    }
    
    generateModelMatrix();
    return true;
}

void Weather::RainParticle::render (Scene &scene) {
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

Weather::Weather (Scene *scene) {
    this->scene = scene;
}

void Weather::toggleRain () {
    this->raining = !this->raining;
}

void Weather::update () {
    if (this->raining) {
        
        random_device rd;
        default_random_engine generator(rd());
        uniform_real_distribution<double>
            distribution(0, (dynamic_cast<Game *>(scene)->level->size) * 2);
        
        auto rainParticle = make_unique<Weather::RainParticle>(
            vec3{
                distribution(generator),
                20,
                distribution(generator),
            }, this);
        scene->objects.push_back(move(rainParticle));
    }
}
