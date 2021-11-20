#pragma once

#include "alien.h"
#include "display.h"
#include "timer.h"
#include "bullet.h"
#include "bunker.h"

class Game
{
private:
    Timer timer;
    Alien aliens[MAX_ALIENS];
    Bullet bullets[MAX_BULLETS];
    Bunker bunkers[MAX_BUNKERS];
    Entity *allEntities[MAX_ENTITIES];
    Display display;
    unsigned char frame[DISP_HEIGHT][DISP_WIDTH];
    void cleanFrame();

public:
    Game();
    void createFrame();
    void initialize();
    void start();
};