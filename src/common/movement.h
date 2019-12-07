//
// Created by František Gič on 02/12/2019.
//

#pragma once

#ifndef DYNABLASTER3D_MOVEMENT_H
#define DYNABLASTER3D_MOVEMENT_H

#include <src/objects/object.h>
#include <src/common/game.h>

class Move {
public:
    bool up;
    bool down;
    bool right;
    bool left;
};

class ComplexPosition {
public:
    Move move;
    bool inCorner;
    bool inCrossRoads;
};

class Movement {
public:
    static Object *getIntersectingObject (Game &scene, Object *object);
    
    static Object *getIntersectingObject (Game &scene, vec3 position);
    
    template<typename T>
    static ComplexPosition getPossibleMove (Game &scene, T *object);
};

#endif //DYNABLASTER3D_MOVEMENT_H
