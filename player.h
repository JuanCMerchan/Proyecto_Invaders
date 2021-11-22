#pragma once

#include "actor.h"
#include "bullet.h"
#include "timer.h"

class Player : public Actor
{
    enum State {SHOOTING, WAITING, DYING};
private:
    static Bullet *bullets;
    State state;
    unsigned long previousShot;
    Timer timer;
public:
    Player();
    void act(bool moveRight, bool moveLeft, bool shoot);
    void initialize(int x, int y, Color color);
    static void setBullets(Bullet *bullets);
    void shoot();
};