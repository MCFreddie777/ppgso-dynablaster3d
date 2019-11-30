#include <glm/glm.hpp>

#include "camera.h"

using namespace std;
using namespace glm;
using namespace ppgso;


Camera::Camera(float fow, float ratio, float near, float far) {
    float fowInRad = (PI / 180.0f) * fow;
    projectionMatrix = perspective(fowInRad, ratio, near, far);
    
    this->update(this->views[this->view]);
}


void Camera::update() {
    viewMatrix = lookAt(current.position, current.position - current.back, current.up);
}

void Camera::update(View view) {
    current = view;
    this->update();
}

void Camera::switchView() {
    view++;
    if (view == views.size()) {
        view = 0;
    }
    this->update(views[view]);
}

void Camera::handleKey(int key) {
    
    // Rotating camera shouldn't be enabled in third person mode
    if (view != 1) {
        float speed = 0.5f;
        
        if (key == GLFW_KEY_BACKSLASH) {
            current.position -= speed * current.back;
        }
        if (key == GLFW_KEY_RIGHT_BRACKET) {
            current.position += speed * current.back;
            
        }
        
        if (key == GLFW_KEY_UP) {
            // TODO: tilt up
        }
        
        if (key == GLFW_KEY_DOWN) {
            // TODO: tilt up
        }
        
        if (key == GLFW_KEY_LEFT) {
            // TODO: instead of move left, tilt left
            current.position -= normalize(cross(current.back, current.up)) * speed;
        }
        
        if (key == GLFW_KEY_RIGHT) {
            current.position += normalize(cross(current.back, current.up)) * speed;
            // TODO: instead of move right, tilt right
        }
        this->update();
    }
}


vec3 Camera::cast(double u, double v) {
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