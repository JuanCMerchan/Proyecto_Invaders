#pragma once

#include "actor.h"
#include "bullet.h"
#include "myRandom.h"

#define MAX_ALIENS 24
#define MAX_SINGLE_ALIEN 8
#define MAX_MOVEMENT 32
#define CHANCE_SHOOT 200

class Alien : public Actor
{
    enum State
    {
        MOVING_RIGHT,
        MOVING_LEFT,
        DYING
    };

private:
    State state;
    int movement;
    static Bullet *bullets;
public:
    Alien();
    void act();
    virtual void moveDown();
    virtual void moveLeft();
    virtual void moveUp();
    virtual void moveRight();
    static void setBullets(Bullet *bullets);
    void shoot();
};