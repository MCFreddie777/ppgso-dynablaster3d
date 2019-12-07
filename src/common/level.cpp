//
// Created by František Gič on 30/11/2019.
//

#include <cstdlib>
#include <cmath>
#include "level.h"
#include "src/objects/block.h"
#include "src/objects/player.h"
#include "src/objects/enemy.h"

using namespace std;

Level::Level (uint size) {
    this->size = size;
    
    this->objects = {
        .blocks =  {
            .maxNumber = (int) ((size * size) * 0.17),
            .number = 0,
        },
        .enemies =  {
            .maxNumber = (int) round(size / 3),
            .number = 0,
        },
        .player =  {
            .maxNumber = 1,
            .number = 0,
        },
    };
    
    this->generate();
}

/**
 * Generates level matrix
 */
void Level::generate () {
    level = vector<vector<char>>(size, vector<char>(size));
    
    srand(time(NULL));
    
    for (uint i = 0; i < this->size; i++) {
        for (uint j = 0; j < this->size; j++) {
            
            // corner walls and middle-aisle blocks
            if ((i == 0 || j == 0 || i == size - 1 || j == size - 1)
                || (i % 2 == 0 && j % 2 == 0)) {
                level[i][j] = ObjectType::WALL;
            }
    
            /* Doesn't seem much random
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
            else if ((random < objects.blocks.spawnRate)) {
                level[i][j] = 'B';
            }
             */
        }
    }
    
    
    vec2 position;
    
    // Generate player
    while (!objects.player.number) {
        position.x = rand() % size;
        position.y = rand() % size;
        
        if (!level[(uint) position.x][(uint) position.y]) {
            level[(uint) position.x][(uint) position.y] = ObjectType::PLAYER;
            objects.player.number++;
        }
    }
    
    int radius = 1;
    
    // Generate enemies
    while (objects.enemies.number < objects.enemies.maxNumber) {
        
        position.x = rand() % (size - 2) + 1;
        position.y = rand() % (size - 2) + 1;
        
        if (canSpawn(position, radius)) {
            level[(uint) position.x][(uint) position.y] = ObjectType::ENEMY;
            objects.enemies.number++;
        }
    }
    
    // Generate destroyable blocks
    while (objects.blocks.number < objects.blocks.maxNumber) {
        
        position.x = rand() % (size - 2) + 1;
        position.y = rand() % (size - 2) + 1;
        
        if (canSpawn(position, radius)) {
            level[(uint) position.x][(uint) position.y] = ObjectType::BLOCK;
            objects.blocks.number++;
        }
    }
}

void Level::create (Scene &scene) {
    
    // Generate ground
    auto plane = make_unique<Block>(vec3{size - 1, 0.8, size - 1}, "grass");
    plane->scale = plane->scale * vec3{size, 0.2, size};
    scene.objects.push_back(move(plane));
    
    // Generate other objects
    for (uint i = 0; i < size; i++) {
        for (uint j = 0; j < size; j++) {
            vec3 position = {i * 2, 2, j * 2};
            switch (level[i][j]) {
                case ObjectType::WALL: {
                    auto wall = make_unique<Block>(position, "wall");
                    scene.objects.push_back(move(wall));
                    break;
                }
                case ObjectType::BLOCK: {
                    auto block = make_unique<Block>(position, "block");
                    scene.objects.push_back(move(block));
                    this->blockCount++;
                    break;
                }
                case ObjectType::PLAYER: {
                    auto player = make_unique<Player>(position);
                    scene.objects.push_back(move(player));
                    break;
                }
                case ObjectType::ENEMY: {
                    auto enemy = make_unique<Enemy>(position);
                    scene.objects.push_back(move(enemy));
                    break;
                }
            }
        }
    }
}

bool Level::canSpawn (vec2 position, int radius) {
    
    bool suitablePos = true;
    
    // object existing on this position
    if (level[(uint) position.x][(uint) position.y])
        return false;
    
    for (
        int i = ((int) position.x - radius);
        i <= ((int) position.x + radius) && suitablePos;
        i++
        ) {
        
        for (
            int j = ((int) position.y - radius);
            j <= ((int) position.y + radius) && suitablePos;
            j++
            ) {
            
            
            // Check boundaries
            if (
                i > 0 &&
                j > 0 &&
                ((uint) i) < this->size &&
                ((uint) j) < this->size
                ) {
                
                // if player or enemy is in radius
                if (
                    level[(uint) i][(uint) j] == ObjectType::PLAYER ||
                    level[(uint) i][(uint) j] == ObjectType::ENEMY
                    ) {
                    suitablePos = false;
                }
            }
        }
    }
    return suitablePos;
}

vector<vector<char>> Level::get () {
    return this->level;
}
