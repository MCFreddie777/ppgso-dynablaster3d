//
// Created by František Gič on 07/12/2019.
//

#include <thread>
#include <stdlib.h>
#include <chrono>
#include "game.h"
#include "scenewindow.h"
#include "weather.h"

void Game::init () {
    
    Scene::init();
    
    this->animate = true;
    
    auto level = make_unique<Level>(this->size);
    this->level = move(level);
    this->level->create(*this);
    
    auto weather = make_unique<Weather>(this);
    this->weather = move(weather);
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
        
                // Toggle weather - raining
            case (GLFW_KEY_U): {
                this->weather->toggleRain();
                break;
            }
                // Set wind direction
            case (GLFW_KEY_I): {
                this->weather->wind -= .026f;
                break;
            }
                // Set wind direction
            case (GLFW_KEY_O): {
                this->weather->wind += .026f;
                break;
            }
            
            default:
                break;
        }
    }
    
        // Move the sun ( "Give me an axis and I will move the sun" ~ArchimedesFero )
    else if (key == GLFW_KEY_B) {
        this->lightDirection.x -= 0.4f;
    }
    else if (key == GLFW_KEY_N) {
        this->lightDirection.x += 0.4f;
    }
    
    // Handle camera
    if (std::find(std::begin(this->camera->controls), std::end(this->camera->controls), key)
        != std::end(this->camera->controls)) {
        this->camera->handleKey(key);
    }
}