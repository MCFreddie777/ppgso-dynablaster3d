//
// Created by František Gič on 30/11/2019.
//

#include <cstdlib>
#include "level.h"
#include "src/objects/block.h"

Level::Level(uint size) {
    this->size = size;
    this->generate();
}

/**
 * Generates level matrix
 */
void Level::generate() {
    level = vector<vector<char>>(size, vector<char>(size));
    
    for (uint i = 0; i < this->size; i++) {
        for (uint j = 0; j < this->size; j++) {
            // TODO: Fill
            level[i][j] = 'W';
        }
    }
}

void Level::create(Scene &scene) {
    for (uint i = 0; i < size; i++) {
        for (uint j = 0; j < size; j++) {
            auto block = make_unique<Block>(vec3{i*2, 0, j*2}, "wall");
            scene.objects.push_back(move(block));
        }
    }
}
