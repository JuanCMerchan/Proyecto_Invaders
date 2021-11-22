#pragma once

#include "entity.h"
#include <stdio.h>

class Actor: public Entity
{
private:

public:
    Actor();
    virtual void moveDown();
    virtual void moveLeft();
    virtual void moveUp();
    virtual void moveRight();
};
