#pragma once

#include "alien.h"
#include "display.h"
#include "timer.h"

#define NUM_ALIENS 10

class Game
{
private:
    Timer timer;
    Alien aliens[NUM_ALIENS];
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