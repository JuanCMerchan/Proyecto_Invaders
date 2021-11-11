#pragma once

#include "actor.h"
#define MAX_MOVEMENT 20

class Alien : public Actor
{
    enum State
    {
        MOVING_RIGHT,
        MOVING_LEFT
    };

private:
    State state;
    int movement;
public:
    Alien();
    void act();
    virtual void moveDown();
    virtual void moveLeft();
    virtual void moveUp();
    virtual void moveRight();
};