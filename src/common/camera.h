#pragma once

#include <memory>
#include <vector>

#include <glm/glm.hpp>
#include <bin/ppgso/lib/ppgso.h>

using namespace glm;
using namespace std;

class Game;

typedef struct {
    vec3 up;
    vec3 position;
    vec3 center;
} View;

class Camera {
private:
    
    vec3 globalUp = vec3{0, 1, 0};
    
    uint view = 0;
    vector<View> views = {
        {
            globalUp,
            {14.0f, 30, -20},
            {14.0f, 2, 14.0f},
        },
        {
            globalUp,
            {2,     4,  0},
            {0,     0, -1},
        }
    };
    
    View current = {
        globalUp,
        {0, 0, 0},
        {0, 0, 0}
    };

public:
    
    mat4 viewMatrix;
    mat4 projectionMatrix;
    
    vector<int> controls = {
        GLFW_KEY_UP,
        GLFW_KEY_DOWN,
        GLFW_KEY_RIGHT,
        GLFW_KEY_LEFT,
        GLFW_KEY_BACKSLASH,
        GLFW_KEY_RIGHT_BRACKET
    };
    
    
    Camera (float fow = 45.0f, float ratio = 1.0f, float near = 0.1f, float far = 10.0f);
    
    void update ();
    
    void update (View view);
    
    void update (vec3 center);
    
    void update (vec3 eye, vec3 center);
    
    void updateWithDirection (vec3 position, short direction);
    
    vec3 getDirectionMatrix (short direction);
    
    vec3 cast (double u, double v);
    
    void switchView (Game *scene);
    
    void handleKey (int key);
    
    bool isFirstPersonMode ();
    
    View getView ();
};

