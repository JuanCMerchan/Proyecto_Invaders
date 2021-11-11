#pragma once

#include "entity.h"

enum Action{M_UP, M_DOWN, M_LEFT, M_RIGHT, SHOOT};

class Actor: public Entity
{
protected:

public:
    Actor();
    virtual void moveDown();
    virtual void moveLeft();
    virtual void moveUp();
    virtual void moveRight();
};
