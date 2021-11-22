#pragma once

#include "actor.h"
#include "bullet.h"
#include "myRandom.h"

#define MAX_ALIENS 32
#define MAX_SINGLE_ALIEN 8
#define MAX_MOVEMENT 32
#define CHANCE_SHOOT 150
#define SQUID_SCORE 100
#define CRAB_SCORE 200
#define OCTOPUS_SCORE 300

class Alien : public Actor
{
    enum State
    {
        MOVING_RIGHT,
        MOVING_LEFT,
        DYING
    };

private:
    int score;
    State state;
    int movement;
    static Bullet *bullets;
public:
    Alien();
    void act();
    void initialize(int x, int y, const Sprites *sprites, Color color, int score);
    int getScore();
    virtual void moveDown();
    virtual void moveLeft();
    virtual void moveUp();
    virtual void moveRight();
    static void setBullets(Bullet *bullets);
    void shoot();
};