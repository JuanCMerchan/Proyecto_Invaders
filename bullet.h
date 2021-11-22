#pragma once

#include "actor.h"

#define MAX_BULLETS 20
#define MAX_TIME_LIVE 150

class Bullet : public Actor
{
    enum State
    {
        MOVING,
        DYING
    };

private:
    State state;
    int timeAlive;
    static Entity *entities[MAX_ENTITIES];
    static int sizeEntities;

public:
    Bullet();
    void act();
    void checkCollisions();
    void initialize(int x, int y, Color color);
    bool isColliding(Entity *entity);
    void moveDown();
    void moveUp();
    void reset(int x, int y, bool friendly);
    static void setEntities(Entity *entities[MAX_ENTITIES]);
};
