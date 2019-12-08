//
// Created by František Gič on 07/12/2019.
//

#include <thread>
#include <chrono>
#include "game.h"
#include "scenewindow.h"

void Game::init () {
    
    Scene::init();
    
    this->animate = true;
    
    auto level = make_unique<Level>(this->size);
    this->level = move(level);
    this->level->create(*this);
}

void Game::update (float time) {
    // End of game when all blocks are destroyed
    
    if (this->level && this->level->blockCount == 0) {
        this->animate = false;
        this_thread::sleep_for(chrono::seconds(2));
        this->windowRef->openMenu();
    }
    
    // Spawn power ups after certain amount of time
    this->time += time;
    if (this->time > 15.0f) {
        this->level->dropPowerUp(*this);
        this->time = 0;
    }
    
    Scene::update(time);
}

void Game::handleKey (int key, int action) {
    if (action == GLFW_PRESS) {
        switch (key) {
            
            //Exit to the menu
            case (GLFW_KEY_ESCAPE): {
                this->windowRef->openMenu();
                break;
            }
                
                // Restart
            case (GLFW_KEY_R): {
                this->windowRef->startGame();
                break;
            }
                // Pause
            case (GLFW_KEY_P): {
                this->animate = !this->animate;
                break;
            }
                
                // Switch camera view
            case (GLFW_KEY_C): {
                this->camera->switchView(this);
                break;
            }
            default:
                break;
        }
    }
    
    // Handle camera
    if (std::any_of(
        begin(this->camera->controls),
        end(this->camera->controls),
        [&] (int i) { return i == key; }
    )) {
        this->camera->handleKey(key);
    }
}