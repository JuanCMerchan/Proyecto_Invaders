#pragma once

#include "alien.h"
#include "display.h"
#include "timer.h"
#include "bullet.h"
#include "bunker.h"
#include "player.h"
#include "control.h"
#include "ufo.h"

#define BASE_TIME_ALIEN 15
#define VARIABLE_TIME_ALIEN 485
#define TIME_UFO 20
#define TIME_BULLET 6
#define TIME_BUNKER 500
#define TIME_PLAYER 1000 / 60
#define TIME_DISPLAY 1000 / 60

#define BUNKER_DISP_HEIGHT 40
#define PLAYER_DISP_HEIGHT 5

class Game
{
private:
    Control control;
    Timer timer;
    Alien aliens[MAX_ALIENS];
    Bullet bullets[MAX_BULLETS];
    Bunker bunkers[MAX_BUNKERS];
    Player player;
    Ufo ufo;
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