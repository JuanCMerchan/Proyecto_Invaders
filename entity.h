#pragma once

#define MAX_ENTITIES 10

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
    int getScore();
    int getX();
    int getY();
    const Sprites *getSprite();
    int getSpriteIndex();
    void initialize(int x, int y, const Sprites *sprites, Color color);
    void loseHealth();
    void nextSprite();
    void setFriendly(bool friendly);
};