#include "actor.h"

Actor::Actor()
{

}

void Actor::moveDown()
{
    this->y++;
}

void Actor::moveLeft()
{
    this->x--;
}

void Actor::moveUp()
{
    this->y--;
}

void Actor::moveRight()
{
    this->x++;
}