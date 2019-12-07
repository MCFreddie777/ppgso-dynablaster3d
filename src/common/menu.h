//
// Created by František Gič on 07/12/2019.
//
#pragma once

#ifndef DYNABLASTER3D_MENU_H
#define DYNABLASTER3D_MENU_H

#include "scene.h"
#include "scenewindow.h"

using namespace std;
using namespace ppgso;


class Menu final : public Scene {

private:
    class MenuObject final : public Object {
        unique_ptr<Mesh> mesh;
        static unique_ptr<Shader> shader;
        unique_ptr<Texture> texture;
    
    
    public:
        MenuObject (vec3 position, string texturePath, string meshPath);
        
        bool update (Scene &scene, float dt) override;
        
        void render (Scene &scene) override;
        
    };
    
    MenuObject *cursor;

public:
    void init ();
    
    void update (float time) override;
    
    void handleKey (int key, int action) override;
};


#endif //DYNABLASTER3D_GAME_H
