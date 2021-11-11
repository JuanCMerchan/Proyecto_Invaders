#include "alien.h"

Alien::Alien()
{
    this->state = MOVING_RIGHT;
    this->movement = 0;
}

void Alien::act()
{
    switch (this->state)
    {
    case State::MOVING_RIGHT:
        if(this->movement == MAX_MOVEMENT)
        {
            this->state = MOVING_LEFT;
        }
        moveRight();
        this->movement++;
        break;

    case State::MOVING_LEFT:
        if(this->movement == 1)
        {
            this->state = MOVING_RIGHT;
        }
        moveLeft();
        this->movement--;
        break;
    default:
        break;
    }
    this->spriteIndex++;
    this->spriteIndex %= this->sprites->numFrames;
}

void Alien::moveDown()
{
    this->y += 2;
}

void Alien::moveLeft()
{
    this->x -= 2;
}

void Alien::moveUp()
{
    this->y -= 2;
}

void Alien::moveRight()
{
    this->x += 2;
}

