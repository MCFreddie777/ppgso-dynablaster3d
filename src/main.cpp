//
// Created by František Gič on 18/11/2019.
//

#include <iostream>
#include <list>
#include <bin/ppgso/lib/ppgso.h>
#include <GLUT/glut.h>

#include "src/common/scene.h"
#include "src/common/camera.h"
#include "src/common/level.h"
#include "src/objects/player.h"

using namespace std;
using namespace glm;
using namespace ppgso;

const unsigned int SIZE = 1024;

class SceneWindow : public Window {

private:
    Scene scene;
    
    static void initScene (Scene &scene) {
        scene.objects.clear();
        scene.animate = true;
        
        /* Handling Camera */
        auto camera = make_unique<Camera>(60.0f, 1.0f, 0.1f, 100.0f);
        scene.camera = move(camera);
        
        auto level = make_unique<Level>(15);
        scene.level = move(level);
        scene.level->create(scene);
    }

public:
    SceneWindow () : Window{"DYNABlaster3D", SIZE, SIZE} {
        hideCursor();
        glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);
        
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        glCullFace(GL_BACK);
        
        initScene(scene);
    }
    
    void onKey (int key, int scanCode, int action, int mods) override {
        scene.keyboard[key] = action;
        
        if (action == GLFW_PRESS) {
            // Start & Reset
            if (key == GLFW_KEY_ENTER || key == GLFW_KEY_R) {
                initScene(scene);
            }
            
            // Pause
            if (key == GLFW_KEY_P) {
                scene.animate = !scene.animate;
            }
            
            // Switch camera view
            if (key == GLFW_KEY_C) {
                scene.camera->switchView();
            }
        }
        
        // Handle camera
        if (std::any_of(
            begin(scene.camera->controls),
            end(scene.camera->controls),
            [&] (int i) { return i == key; }
        )) {
            scene.camera->handleKey(key);
        }
    }
    
    
    void onIdle () override {
        static auto time = (float) glfwGetTime();
        
        // Compute time delta
        float dt = scene.animate ? (float) glfwGetTime() - time : 0;
        
        time = (float) glfwGetTime();
        
        glClearColor(.5f, .5f, .5f, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        scene.update(dt);
        scene.render();
    }
};

int main () {
    SceneWindow window;
    
    while (window.pollEvents()) {}
    
    return EXIT_SUCCESS;
}