#include "alien.h"

Bullet *Alien::bullets;

Alien::Alien()
{
    this->state = MOVING_RIGHT;
    this->movement = 0;
}

void Alien::act()
{
    if (this->alive)
    {
        switch (this->state)
        {
        case State::MOVING_RIGHT:
            if (this->movement == MAX_MOVEMENT)
            {
                this->state = MOVING_LEFT;
            }
            moveRight();
            this->movement++;
            if (myRandom::getRandomNumber(CHANCE_SHOOT) == 1)
            {
                shoot();
            }
            break;

        case State::MOVING_LEFT:
            if (this->movement == 1)
            {
                this->state = MOVING_RIGHT;
            }
            moveLeft();
            this->movement--;
            if (myRandom::getRandomNumber(CHANCE_SHOOT) == 1)
            {
                shoot();
            }
            break;
        default:
            break;
        }
        this->spriteIndex++;
        this->spriteIndex %= this->sprites->numFrames;
    }
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

void Alien::setBullets(Bullet *bullets)
{
    Alien::bullets = bullets;
}

void Alien::shoot()
{
    int x;
    int y;
    x = this->getX() + (this->getSprite()->width / 2);
    y = this->getY() + this->getSprite()->length;
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        if (!(Alien::bullets[i].getAlive()))
        {
            Alien::bullets[i].reset(x, y, false);
            break;
        }
    }
}