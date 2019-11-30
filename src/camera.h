#pragma once

#include <memory>
#include <vector>

#include <glm/glm.hpp>
#include <bin/ppgso/lib/ppgso.h>

using namespace glm;
using namespace std;

typedef struct {
    vec3 up;
    vec3 position;
    vec3 back;
} View;

class Camera {
private:
    uint view = 0;
    vector<View> views = {
            {
                    {0, 1, 1},
                    {18.5f, 34, -20},
                    {0, 0.95f, -1},
            },
            {
                    {0, 1, 0},
                    {0, 2, 0},
                    {0, 0, -1},
            }
    };
    
    View current = {
            {0, 1, 0},
            {0, 0, 0},
            {0, 0, -1}
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
    
    
    Camera(float fow = 45.0f, float ratio = 1.0f, float near = 0.1f, float far = 10.0f);
    
    void update();
    
    void update(View view);
    
    vec3 cast(double u, double v);
    
    void switchView();
    
    void handleKey(int key);
    
};

