#include "alien.h"

Bullet *Alien::bullets;

Alien::Alien()
{
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
                moveDown();
                this->state = MOVING_LEFT;
            }
            else
            {
                moveRight();
                this->movement++;
            }
            if (myRandom::getRandomNumber(CHANCE_SHOOT) == 1)
            {
                shoot();
            }
            if (this->health == 0)
            {
                this->state = State::DYING;
            }
            break;

        case State::MOVING_LEFT:
            if (this->movement == 1)
            {
                moveDown();
                this->state = MOVING_RIGHT;
            }
            else
            {
                moveLeft();
                this->movement--;
            }
            if (myRandom::getRandomNumber(CHANCE_SHOOT) == 1)
            {
                shoot();
            }
            if (this->health == 0)
            {
                this->state = State::DYING;
            }
            break;

        case State::DYING:
            this->alive = false;
            break;
        default:
            break;
        }
        this->spriteIndex++;
        this->spriteIndex %= this->sprites->numFrames;
    }
}

void Alien::initialize(int x, int y, const Sprites *sprites, Color color, int score)
{
    Entity::initialize(x, y, sprites, color);
    this->health = 1;
    this->movement = 0;
    this->state = State::MOVING_RIGHT;
    this->score = score;
}

int Alien::getScore()
{
    return this->score;
}

void Alien::moveDown()
{
    this->y += 8;
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