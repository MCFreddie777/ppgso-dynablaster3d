//
// Created by František Gič on 07/12/2019.
//

#include "scenewindow.h"

#include "src/common/camera.h"
#include "src/common/game.h"
#include "src/common/menu.h"

const unsigned int SIZE = 1024;

template<typename T>
void SceneWindow::initScene (T *currentScene) {
    currentScene->init();
    
    /* Handling Camera */
    auto camera = make_unique<Camera>(60.0f, 1.0f, 0.1f, 100.0f);
    currentScene->camera = move(camera);
    
    this->scene = currentScene;
    this->scene->windowRef = this;
}

SceneWindow::SceneWindow () : Window{"DYNABlaster3D", SIZE, SIZE} {
    this->game = new Game();
    this->menu = new Menu();
    
    hideCursor();
    glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
    
    this->openMenu();
}

void SceneWindow::onKey (int key, int scanCode, int action, int mods) {
    scene->keyboard[key] = action;
    scene->handleKey(key, action);
}


void SceneWindow::onIdle () {
    
    static auto time = (float) glfwGetTime();
    float dt = 0;

// Compute time delta
    if (dynamic_cast<Game *>(this->scene))
        dt = dynamic_cast<Game *>(this->scene)->animate ? (float) glfwGetTime() - time : 0;
    
    time = (float) glfwGetTime();
    
    glClearColor(.7f, .93f, .96f, 0);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    scene->update(dt);
    scene->render();
    
}

void SceneWindow::openMenu () {
    initScene(this->menu);
}

void SceneWindow::startGame () {
    initScene(game);
}