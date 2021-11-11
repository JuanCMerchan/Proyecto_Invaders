#include "bullet.h"

Entity *Bullet::entities[MAX_ENTITIES];
int Bullet::sizeEntities;

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
            if (this->health == 0)
            {
                this->state == State::DYING;
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
    for (int i = 0; i < this->sizeEntities; i++)
    {
        if (this->entities[i]->getHealth() > 0 && isColliding(this->entities[i]))
        {
            if (this->friendly || (this->entities[i]->getFriendly()))
            {
                this->entities[i]->loseHealth();
                loseHealth();
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
}

bool Bullet::isColliding(Entity *entity)
{
    if (this->x >= entity->getX() + entity->getSprite()->width || this->x + this->sprites->width <= entity->getX())
    {
        return false;
    }
    if (this->y <= entity->getY() + entity->getSprite()->length || this->y + this->sprites->length >= entity->getY())
    {
        return false;
    }
    return true;
}

void Bullet::reset(int x, int y, bool friendly)
{
    this->x = x;
    this->y = y;
    this->friendly = friendly;
    this->health = 1;
    this->alive = true;
}

void Bullet::setEntities(Entity *entities[MAX_ENTITIES])
{
    for (int i = 0; i < MAX_ENTITIES; i++)
    {
        Bullet::entities[i] = entities[i];
    }
}