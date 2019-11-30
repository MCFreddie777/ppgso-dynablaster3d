//
// Created by František Gič on 18/11/2019.
//

#include <iostream>
#include <list>
#include <bin/ppgso/lib/ppgso.h>
#include <GLUT/glut.h>

using namespace std;
using namespace glm;
using namespace ppgso;

const unsigned int SIZE = 1024;

class SceneWindow : public Window {

private:
    void initScene() {
    }

public:
    SceneWindow() : Window{"DYNABlaster3D", SIZE, SIZE} {
        hideCursor();
        glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);
        
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        glCullFace(GL_BACK);
        
        initScene();
    }
    
    void onKey(int key, int scanCode, int action, int mods) override {
    }
    
    
    void onIdle() override {
        glClearColor(.5f, .5f, .5f, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
};

int main() {
    SceneWindow window;
    
    while (window.pollEvents()) {}
    
    return EXIT_SUCCESS;
}