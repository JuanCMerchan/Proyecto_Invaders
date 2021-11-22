#include "bullet.h"

Entity *Bullet::entities[MAX_ENTITIES];
int Bullet::sizeEntities;

Bullet::Bullet()
{
}

void Bullet::act()
{
    if (this->alive)
    {
        switch (this->state)
        {
        case State::MOVING:
            if (friendly)
            {
                moveUp();
            }
            else
            {
                moveDown();
            }
            checkCollisions();
            this->timeAlive++;
            if (this->health == 0 || this->timeAlive == MAX_TIME_LIVE)
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
    }
}

void Bullet::checkCollisions()
{
    for (int i = 0; i < MAX_ENTITIES; i++)
    {
        if (Bullet::entities[i]->getHealth() > 0 && isColliding(Bullet::entities[i]) && this != Bullet::entities[i])
        {
            if (this->friendly || (Bullet::entities[i]->getFriendly()))
            {
                Bullet::entities[i]->loseHealth();
                this->loseHealth();
                break;
            }
        }
    }
}

void Bullet::initialize(int x, int y, const Sprites *sprites, Color color)
{
    Entity::initialize(x, y, sprites, color);
    this->health = 1;
    this->alive = false;
    this->timeAlive = 0;
}

bool Bullet::isColliding(Entity *entity)
{
    if (this->x >= entity->getX() + entity->getSprite()->width || this->x + this->sprites->width <= entity->getX())
    {
        return false;
    }
    if (this->y >= entity->getY() + entity->getSprite()->length || this->y + this->sprites->length <= entity->getY())
    {
        return false;
    }
    return true;
}

void Bullet::moveDown()
{
    this->y += 2;
}

void Bullet::moveUp()
{
    this->y -= 2;
}

void Bullet::reset(int x, int y, bool friendly)
{
    this->x = x;
    this->y = y;
    this->friendly = friendly;
    this->health = 1;
    this->alive = true;
    this->timeAlive = 0;
    this->state = State::MOVING;
    this->sprites = &BULLET_SPRITE;
    this->spriteIndex = 0;
}

void Bullet::setEntities(Entity *entities[MAX_ENTITIES])
{
    for (int i = 0; i < MAX_ENTITIES; i++)
    {
        Bullet::entities[i] = entities[i];
    }
}