//
// Created by František Gič on 02/12/2019.
//

#ifndef DYNABLASTER3D_MOVEMENT_H
#define DYNABLASTER3D_MOVEMENT_H

#include "scene.h"

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
    bool intersects;
    bool inCorner;
    bool inCrossRoads;
};

class Movement {
public:
    template<typename T>
    static ComplexPosition getPossibleMove (Scene &scene, T *object);
};

#endif //DYNABLASTER3D_MOVEMENT_H
