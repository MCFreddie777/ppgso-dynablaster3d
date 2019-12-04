//
// Created by František Gič on 30/11/2019.
//

#ifndef DYNABLASTER3D_SCENE_H
#define DYNABLASTER3D_SCENE_H

#include <memory>
#include <map>
#include <list>

#include "src/objects/object.h"
#include "src/common/camera.h"

class Scene {
public:
    bool animate = true;
    
    void update (float time);
    
    void render ();
    
    std::vector<Object *> intersect (const glm::vec3 &position, const glm::vec3 &direction);
    
    
    // Camera object
    std::unique_ptr<Camera> camera;
    
    // All objects to be rendered in scene
    std::list<std::unique_ptr<Object>> objects;
    
    // Keyboard state
    std::map<int, int> keyboard;
    
    // Lights, in this case using only simple directional diffuse lighting
    glm::vec3 lightDirection{-1.0f, 5.0f, -1.0f};
    glm::vec3 lightDirection2{-1.0f, 2.0f, -1.0f};
    glm::vec3 lightColor{1.0f, 1.0f, 1.0f};
    glm::vec3 lightColor2{0, 1, 1};
    
    
    // Store cursor state
    struct {
        double x, y;
        bool left, right;
    } cursor;
    
};


#endif //DYNABLASTER3D_SCENE_H
