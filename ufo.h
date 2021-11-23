#pragma once

#include "actor.h"
#include "timer.h"
#include "bullet.h"

#define UFO_CD 10000
#define UFO_SCORE 1000

class Ufo : public Actor
{
    enum State
    {
        MOVING_RIGHT,
        MOVING_LEFT,
        WAITING_RIGHT,
        WAITING_LEFT,
        DYING
    };

private:
    Timer timer;
    State state;
    Entity *player;
    static Bullet *bullets;
    unsigned long previous;
    bool shot;
    int score;
public:
    Ufo();
    void act();
    void initialize(Color color);
    int getScore();
    void moveLeft();
    void moveRight();
    void reset();
    static void setBullets(Bullet *bullets);
    void setPlayer(Entity *player);
    void shoot();
};