#include "entity.h"

Entity::Entity()
{
    
}

bool Entity::getAlive()
{
    return this->alive;
}

Color Entity::getColor()
{
    return this->color;
}

bool Entity::getFriendly()
{
    return this->friendly;
}

int Entity::getHealth()
{
    return this->health;
}

const Sprites *Entity::getSprite()
{
    return this->sprites;
}

int Entity::getSpriteIndex()
{
    return spriteIndex;
}

int Entity::getX()
{
    return this->x;
}

int Entity::getY()
{
    return this->y;
}

void Entity::initialize(int x, int y, const Sprites *sprites, Color color)
{
    this->x = x;
    this->y = y;
    this->sprites = sprites;
    this->color = color;
    this->health = health;
    this->spriteIndex = 0;
}

void Entity::loseHealth()
{
    health--;
    //Todo change sprite to explosion
}

void Entity::nextSprite()
{
    this->spriteIndex++;
}

void Entity::setFriendly(bool friendly)
{
    this->friendly = friendly;
}