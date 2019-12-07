//
// Created by František Gič on 18/11/2019.
//

#pragma once

#ifndef DYNABLASTER3D_SCENEWINDOW_H
#define DYNABLASTER3D_SCENEWINDOW_H

#include <iostream>
#include <list>
#include <bin/ppgso/lib/ppgso.h>
#include <GLUT/glut.h>

#include "src/common/scene.h"

class Menu;

class Game;

using namespace std;
using namespace glm;
using namespace ppgso;

class SceneWindow : public Window {

private:
    Game *game;
    Menu *menu;
    Scene *scene;
    
    template<typename T>
    void initScene (T *currentScene);

public:
    SceneWindow ();
    
    void onKey (int key, int scanCode, int action, int mods) override;
    
    void onIdle () override;
    
    void openMenu ();
    
    void startGame ();
    
};

#endif //DYNABLASTER3D_SCENEWINDOW_H
