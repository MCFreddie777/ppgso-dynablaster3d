//
// Created by František Gič on 30/11/2019.
//

#include "scene.h"

void Scene::init () {
    this->objects.clear();
    this->lightReset();
}

void Scene::update (float time) {
    
    // Use iterator to update all objects so we can remove while iterating
    auto i = std::begin(objects);
    
    while (i != std::end(objects)) {
        // Update and remove from list if needed
        auto obj = i->get();
        if (!obj->update(*this, time))
            i = objects.erase(
                i); // NOTE: no need to call destructors as we store shared pointers in the scene
        else
            ++i;
    }
}

void Scene::render () {
    // Simply render all objects
    for (auto &obj : objects) {
        obj->render(*this);
    }
}

std::vector<Object *> Scene::intersect (const glm::vec3 &position, const glm::vec3 &direction) {
    std::vector<Object *> intersected = {};
    for (auto &object : objects) {
        // Collision with sphere of size object->scale.x
        auto oc = position - object->position;
        auto radius = object->scale.x;
        auto a = glm::dot(direction, direction);
        auto b = glm::dot(oc, direction);
        auto c = glm::dot(oc, oc) - radius * radius;
        auto dis = b * b - a * c;
        
        if (dis > 0) {
            auto e = sqrt(dis);
            auto t = (-b - e) / a;
    
            if (t > 0) {
                intersected.push_back(object.get());
                continue;
            }
            
            t = (-b + e) / a;
    
            if (t > 0) {
                intersected.push_back(object.get());
                continue;
            }
        }
    }
    
    return intersected;
}

void Scene::lightReset () {
    this->lightDirection = vec3{-1.0f, 5.0f, -1.0f};
    this->lightDirection2 = vec3{-1.0f, 2.0f, -1.0f};
    this->lightColor = vec3{1.0f, 1.0f, 1.0f};
    this->lightColor2 = vec3{0, 1, 1};
}

void Scene::handleKey (int key, int action) {};


