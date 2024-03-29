#include <glm/glm.hpp>

#include "camera.h"
#include "game.h"
#include "../objects/player.h"

using namespace std;
using namespace glm;
using namespace ppgso;


Camera::Camera (float fow, float ratio, float near, float far) {
    float fowInRad = (PI / 180.0f) * fow;
    projectionMatrix = perspective(fowInRad, ratio, near, far);
    this->update(this->views[this->view]);
}


void Camera::update () {
    this->update(current.position, current.center);
}

void Camera::update (vec3 eye, vec3 center) {
    viewMatrix = lookAt(eye, center, globalUp);
}

void Camera::update (View view) {
    current = view;
    this->update();
}

void Camera::update (vec3 center) {
    viewMatrix = lookAt(current.position, center, globalUp);
}

void Camera::updateWithDirection (vec3 position, short direction) {
    current.position = position - this->getDirectionMatrix(direction);
    current.center = position;
    this->update();
}

vec3 Camera::getDirectionMatrix (short direction) {
    switch (direction) {
        case 0: {
            return vec3{0, -3, 6};
        }
        case 1: {
            return vec3{-6, -3, 0};
        }
        case 2: {
            return vec3{0, -3, -6};
        }
        case 3: {
            return vec3{6, -3, 0};
        }
    }
}

void Camera::switchView (Game *scene) {
    view++;
    if (view == views.size()) {
        view = 0;
    };
    if (view == 1) {
        
        views[view].position =
            scene->player->position - this->getDirectionMatrix(scene->player->direction);
        
        views[view].center = scene->player->position;
    }
    this->update(views[view]);
}

void Camera::handleKey (int key) {
    
    // Rotating camera shouldn't be enabled in third person mode
    if (view != 1) {
        float speed = 0.5f;
        
        if (key == GLFW_KEY_BACKSLASH) {
            current.position -= (current.center - current.position) * (speed / 2);
        }
        if (key == GLFW_KEY_RIGHT_BRACKET) {
            current.position += (current.center - current.position) * (speed / 2);
        }
        
        if (key == GLFW_KEY_UP) {
            current.center.y += speed;
        }
        
        if (key == GLFW_KEY_DOWN) {
            current.center.y -= speed;
        }
        
        if (key == GLFW_KEY_LEFT) {
            current.center.x += speed;
        }
        
        if (key == GLFW_KEY_RIGHT) {
            current.center.x -= speed;
        }
        this->update();
    }
};


vec3 Camera::cast (double u, double v) {
    // Create point in Screen coordinates
    vec4 screenPosition{u, v, 0.0f, 1.0f};
    
    // Use inverse matrices to get the point in world coordinates
    auto invProjection = inverse(projectionMatrix);
    auto invView = inverse(viewMatrix);
    
    // Compute position on the camera plane
    auto planePosition = invView * invProjection * screenPosition;
    planePosition /= planePosition.w;
    
    // Create direction vector
    auto direction = normalize(planePosition - vec4{current.position, 1.0f});
    return vec3{direction};
}

bool Camera::isFirstPersonMode () {
    return view == 1;
}

View Camera::getView () {
    return this->current;
}