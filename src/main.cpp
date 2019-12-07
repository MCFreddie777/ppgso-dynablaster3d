//
// Created by František Gič on 18/11/2019.
//

#include <iostream>
#include <list>
#include <bin/ppgso/lib/ppgso.h>
#include <GLUT/glut.h>

#include "src/common/scene.h"
#include "src/common/game.h"
#include "src/common/camera.h"
#include "src/common/level.h"
#include "src/objects/player.h"

using namespace std;
using namespace glm;
using namespace ppgso;

const unsigned int SIZE = 1024;

class SceneWindow : public Window {

private:
    Game game;
    Scene *scene;
    
    template<typename T>
    void initScene (T &currentScene) {
        currentScene.init();
        
        /* Handling Camera */
        auto camera = make_unique<Camera>(60.0f, 1.0f, 0.1f, 100.0f);
        currentScene.camera = move(camera);
        
        this->scene = &currentScene;
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
    
        this->scene = nullptr;
        // menu?
        initScene(game);
    }
    
    void onKey (int key, int scanCode, int action, int mods) override {
        scene->keyboard[key] = action;
        
        if (action == GLFW_PRESS) {
    
            if (key == GLFW_KEY_ENTER) {
                initScene(this->game);
            }
    
            if (dynamic_cast<Game *>(this->scene)) {
        
                // Start & Reset
                if (key == GLFW_KEY_R) {
                    initScene(*dynamic_cast<Game *>(this->scene));
                }
        
                // Pause
                if (key == GLFW_KEY_P) {
                    dynamic_cast<Game *>(this->scene)->animate = !dynamic_cast<Game *>(this->scene)
                        ->animate;
                }
        
                // Switch camera view
                if (key == GLFW_KEY_C) {
                    scene->camera->switchView();
                }
            }
        }
    
        if (dynamic_cast<Game *>(this->scene)) {
            // Handle camera
            if (std::any_of(
                begin(scene->camera->controls),
                end(scene->camera->controls),
                [&] (int i) { return i == key; }
            )) {
                scene->camera->handleKey(key);
            }
        }
    }
    
    
    void onIdle () override {
    
        static auto time = (float) glfwGetTime();
        float dt = 0;
        // Compute time delta
        if (dynamic_cast<Game *>(this->scene))
            dt = dynamic_cast<Game *>(this->scene)->animate ? (float) glfwGetTime() - time : 0;
        
        time = (float) glfwGetTime();
        
        glClearColor(.5f, .5f, .5f, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
        scene->update(dt);
        scene->render();
    }
};

int main () {
    SceneWindow window;
    
    while (window.pollEvents()) {}
    
    return EXIT_SUCCESS;
}