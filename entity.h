#pragma once

#define MAX_ENTITIES 58

#include "sprites.h"

enum Color {RED, BLUE, GREEN, YELLOW, PINK};

class Entity
{
protected:
    int x;
    int y;
    Color color;
    int health;
    const Sprites *sprites;
    int spriteIndex;
    bool alive;
    bool friendly;

public:
    Entity();
    bool getAlive();
    Color getColor();
    bool getFriendly();
    int getHealth();
    int getX();
    int getY();
    const Sprites *getSprite();
    int getSpriteIndex();
    void initialize(int x, int y, const Sprites *sprites, Color color);
    virtual void loseHealth();
};