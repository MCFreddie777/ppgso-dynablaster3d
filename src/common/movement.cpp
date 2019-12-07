//
// Created by František Gič on 02/12/2019.
//

#include <src/objects/block.h>
#include <src/objects/player.h>
#include <src/objects/enemy.h>
#include <src/objects/bomb.h>
#include "movement.h"
#include "game.h"

Object *Movement::getIntersectingObject (Game &scene, Object *object) {
    for (auto &obj : scene.objects) {
        
        // Ignore self in scene
        if (obj.get() == object)
            continue;
        
        if (
            distance(object->position.z, obj->position.z) == 0 &&
            distance(object->position.x, obj->position.x) == 0 &&
            object->position.y == obj->position.y
            ) {
            return obj.get();
        }
    }
}

Object *Movement::getIntersectingObject (Game &scene, vec3 position) {
    for (auto &obj : scene.objects) {
        
        if (
            distance(position.z, obj->position.z) == 0 &&
            distance(position.x, obj->position.x) == 0 &&
            position.y == obj->position.y
            ) {
            return obj.get();
        }
    }
    return nullptr;
}

template<typename T>
ComplexPosition Movement::getPossibleMove (Game &scene, T *object) {
    
    ComplexPosition position{
        {
            true,
            true,
            true,
            true,
            
        },
        false,
        false
    };
    
    for (auto &obj : scene.objects) {
        
        // Ignore self in scene
        if (obj.get() == object)
            continue;
        
        
        auto block = dynamic_cast<Block *>(obj.get());
        auto bomb = dynamic_cast<Bomb *>(obj.get());
        
        if (!block && !bomb)
            continue;
        
        Object *o = (block) ? (Object *) block : (Object *) bomb;
    
        if (
            distance(object->position.z, o->position.z) == 2
            && o->position.x == object->position.x &&
            o->position.y == object->position.y
            ) {
            if (o->position.z - object->position.z == 2) {
                position.move.up = false;
            }
            else {
                position.move.down = false;
            }
        }
    
        if (
            distance(object->position.x, o->position.x) == 2 &&
            o->position.z == object->position.z &&
            o->position.y == object->position.y
            ) {
            if (o->position.x - object->position.x == 2) {
                position.move.left = false;
            }
            else {
                position.move.right = false;
            }
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


template ComplexPosition Movement::getPossibleMove<Player> (Game &scene, Player *player);

template ComplexPosition Movement::getPossibleMove<Enemy> (Game &scene, Enemy *enemy);

