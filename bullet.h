#pragma once

#include "actor.h"

class Bullet : public Actor
{
    enum State {MOVING, DYING};
private:
    State state;
    static Entity *entities[MAX_ENTITIES];
    static int sizeEntities;
    
public:
    Bullet();
    void act();   
    void checkCollisions();
    void initialize(int x, int y, const Sprites *sprites, Color color); 
    bool isColliding(Entity *entity);
    void reset(int x, int y, bool friendly);
    static void setEntities(Entity *entities[MAX_ENTITIES]);
};


