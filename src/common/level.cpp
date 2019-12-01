//
// Created by František Gič on 30/11/2019.
//

#include <cstdlib>
#include <cmath>
#include "level.h"
#include "src/player.h"
#include "src/objects/block.h"
#include "src/objects/plane.h"

using namespace std;

Level::Level(uint size) {
    this->size = size;
    this->objects = {
            .blocks =  {
                    .maxNumber = 0,
                    .number = 0,
                    .spawnRate = 0.37
            },
            .enemies =  {
                    .maxNumber = (int) round(size / 3),
                    .number = 0,
                    .spawnRate = 0.13
            },
            .player =  {
                    .maxNumber = 1,
                    .number = 0,
                    .spawnRate = 0.05
            },
    };
    
    this->generate();
}

/**
 * Generates level matrix
 */
void Level::generate() {
    level = vector<vector<char>>(size, vector<char>(size));
    
    srand(time(NULL));
    
    for (uint i = 0; i < this->size; i++) {
        for (uint j = 0; j < this->size; j++) {
            
            // corner walls and middle-aisle blocks
            if ((i == 0 || j == 0 || i == size - 1 || j == size - 1)
                || (i % 2 == 0 && j % 2 == 0)) {
                level[i][j] = 'W';
                continue;
            }
            
            double random = rand() / (RAND_MAX + 1.);
            
            if ((random < objects.player.spawnRate)
                && (objects.player.number < objects.player.maxNumber)) {
                
                level[i][j] = 'P';
                objects.player.number++;
            }
            else if ((random < objects.enemies.spawnRate)
                     && (objects.enemies.number < objects.enemies.maxNumber)) {
                level[i][j] = 'E';
                objects.enemies.number++;
            }
            else if (random < objects.blocks.spawnRate) {
                level[i][j] = 'B';
            }
            else {
                level[i][j] = '-';
            }
        }
    }
}

void Level::create(Scene &scene) {
    
    // Generate ground
    auto plane = make_unique<Plane>(vec3{0, 0, 0}, size);
    scene.objects.push_back(move(plane));
    
    // Generate other objects
    for (uint i = 0; i < size; i++) {
        for (uint j = 0; j < size; j++) {
            vec3 position = {i * 2, 2, j * 2};
            if (level[i][j] == 'W') {
                auto wall = make_unique<Block>(position, "wall");
                scene.objects.push_back(move(wall));
            }
            else if (level[i][j] == 'B') {
                auto block = make_unique<Block>(position, "block");
                scene.objects.push_back(move(block));
            }
            else if (level[i][j] == 'P') {
                auto player = make_unique<Player>(position);
                scene.objects.push_back(move(player));
            }
        }
    }
    
}
