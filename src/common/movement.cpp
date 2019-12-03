//
// Created by František Gič on 02/12/2019.
//

#include <src/objects/block.h>
#include <src/objects/player.h>
#include <src/objects/enemy.h>
#include "movement.h"
#include "scene.h"


template<typename T>
Move Movement::getPossibleMove (Scene &scene, T *object) {
    Move movement = {
        true,
        true,
        true,
        true,
        false,
        false
    };
    for (auto &obj : scene.objects) {
        
        // Ignore self in scene
        if (obj.get() == object)
            continue;
        
        auto block = dynamic_cast<Block *>(obj.get());
        if (!block) continue;
        
        if (distance(object->position.z, block->position.z) == 2
            && block->position.x == object->position.x) {
            
            if (block->position.z - object->position.z == 2) {
                movement.up = false;
            }
            else movement.down = false;
        }
        
        if (distance(object->position.x, block->position.x) == 2
            && block->position.z == object->position.z) {
            
            if (block->position.x - object->position.x == 2) {
                movement.left = false;
            }
            else movement.right = false;
        }
    }
    
    
    if ((movement.up + movement.down + movement.left + movement.right) > 2)
        movement.inCrossRoads = true;
    
    if (((movement.up + movement.down + movement.left + movement.right) == 2) &&
        (
            ((movement.up || movement.down) && (movement.up != movement.down)) ||
            ((movement.left || movement.right) && (movement.left != movement.right))
        )
        )
        movement.inCorner = true;
    
    return movement;
}

template Move Movement::getPossibleMove<Player> (Scene &scene, Player *player);

template Move Movement::getPossibleMove<Enemy> (Scene &scene, Enemy *enemy);
