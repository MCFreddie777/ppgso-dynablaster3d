//
// Created by František Gič on 02/12/2019.
//

#include <src/objects/block.h>
#include <src/objects/player.h>
#include <src/objects/enemy.h>
#include <src/objects/bomb.h>
#include <src/objects/fire.h>
#include "movement.h"
#include "game.h"

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
        false,
        false
    };
    
    auto i = std::begin(scene.objects);
    while (i != std::end(scene.objects)) {
        bool iterate = true;
        
        unique_ptr<Object> &obj = *i;
        
        // Ignore self in scene
        if (obj.get() == object) {
            i++;
            continue;
        }
        
        // Check for intersections
        if (
            distance(object->position.z, obj->position.z) == 0 &&
            distance(object->position.x, obj->position.x) == 0
            ) {
    
            // Player dies when intersects with enemy
            if (dynamic_cast<Player *>(object) && dynamic_cast<Enemy *>(obj.get())) {
                position.intersects = true;
            }
    
            // Both player and enemy dies when intersects with fire
            if (
                (dynamic_cast<Player *>(object) || dynamic_cast<Enemy *>(object)) &&
                dynamic_cast<Fire *>(obj.get())
                ) {
                position.intersects = true;
            }
    
            // If fire meets the block, block is removed from the scene
            if (
                dynamic_cast<Fire *>(object) &&
                dynamic_cast<Block *>(obj.get()) &&
                (dynamic_cast<Block *>(obj.get()))->type == "block"
                ) {
                i = scene.objects.erase(i);
                scene.level->blockCount--;
                continue;
            }
        }
        
        auto block = dynamic_cast<Block *>(obj.get());
        auto bomb = dynamic_cast<Bomb *>(obj.get());
        
        if (!block && !bomb) {
            i++;
            continue;
        }
        
        Object *o = (block) ? (Object *) block : (Object *) bomb;
        
        if (distance(object->position.z, o->position.z) == 2
            && o->position.x == object->position.x) {
            
            if (o->position.z - object->position.z == 2) {
                position.move.up = false;
            }
            else position.move.down = false;
        }
        
        if (distance(object->position.x, o->position.x) == 2
            && o->position.z == object->position.z) {
            
            if (o->position.x - object->position.x == 2) {
                position.move.left = false;
            }
            else position.move.right = false;
        }
        i++;
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

template ComplexPosition Movement::getPossibleMove<Fire> (Game &scene, Fire *fire);



