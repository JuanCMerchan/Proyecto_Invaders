#pragma once

#include "entity.h"

#define MAX_BUNKERS 4

class Bunker : public Entity
{
    enum State
    {
        EXISTING,
        DYING
    };

private:
    State state;

public:
    Bunker();
    void act();
    void initialize(int x, int y, const Sprites *sprites, Color color);
};
