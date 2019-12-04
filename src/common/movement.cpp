//
// Created by František Gič on 02/12/2019.
//

#include <src/objects/block.h>
#include <src/objects/player.h>
#include <src/objects/enemy.h>
#include "movement.h"
#include "scene.h"


template<typename T>
ComplexPosition Movement::getPossibleMove (Scene &scene, T *object) {
    
    ComplexPosition position{
        {
            true,
            true,
            true,
            true,
            
        },
        false,
        false,
        false
    };
    
    for (auto &obj : scene.objects) {
        
        // Ignore self in scene
        if (obj.get() == object)
            continue;
        
        if (dynamic_cast<Enemy *>(obj.get())) {
            if (
                distance(object->position.z, obj->position.z) == 0 &&
                distance(object->position.x, obj->position.x) == 0
                ) {
                if (dynamic_cast<Player *>(object)) {
                    position.intersects = true;
                }
            }
        }
        
        auto block = dynamic_cast<Block *>(obj.get());
        if (!block) continue;
        
        
        if (distance(object->position.z, block->position.z) == 2
            && block->position.x == object->position.x) {


//            if (dynamic_cast<Enemy *>(object)) {
//                std::cout << "Object.GetType(): " << typeid(object).name() << '\n';
//                position.intersects = object;
//            }
            
            if (block->position.z - object->position.z == 2) {
                position.move.up = false;
            }
            else position.move.down = false;
        }
        
        if (distance(object->position.x, block->position.x) == 2
            && block->position.z == object->position.z) {
            
            if (block->position.x - object->position.x == 2) {
                position.move.left = false;
            }
            else position.move.right = false;
        }
    }
    
    
    if ((position.move.up + position.move.down + position.move.left + position.move.right) > 2)
        position.inCrossRoads = true;
    
    if (
        ((position.move.up + position.move.down + position.move.left + position.move.right) == 2) &&
        (
            (
                (position.move.up || position.move.down) &&
                (position.move.up != position.move.down)
            ) ||
            (
                (position.move.left || position.move.right) &&
                (position.move.left != position.move.right)
            )
        )
        )
        position.inCorner = true;
    
    return position;
}

template ComplexPosition Movement::getPossibleMove<Player> (Scene &scene, Player *player);

template ComplexPosition Movement::getPossibleMove<Enemy> (Scene &scene, Enemy *enemy);

