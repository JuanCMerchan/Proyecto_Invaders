#pragma once

#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <termios.h>

class Control
{
private:
    bool moveLeft;
    bool moveRight;
    bool shoot;
    termios oldt;
    termios newt;
    struct timeval tv;
    fd_set rdfs;
public:
    Control();
    void initialize();
    void deInitialize();
    void getKeyPresses();
    bool getMoveLeft();
    bool getMoveRight();
    bool getShoot();
};