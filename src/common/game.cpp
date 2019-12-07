//
// Created by František Gič on 07/12/2019.
//

#include "game.h"


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
    }
    
    Scene::update(time);
}