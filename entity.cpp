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
    this->spriteIndex = 0;
    this->alive = true;
}

void Entity::loseHealth()
{
    this->health--;
    this->spriteIndex++;
    this->spriteIndex %= this->sprites->numFrames;
    if(this->health == 0)
    {
        int newX;
        int newY;
        newX = this->x + this->sprites->width / 2;
        newY = this->y + this->sprites->length / 2;
        newX -= EXPLOTION_SPRITE.width / 2;
        newY -= EXPLOTION_SPRITE.length / 2;
        this->sprites = &EXPLOTION_SPRITE;
        this->x = newX;
        this->y = newY;
        this->spriteIndex = 0;
    }
}

void Entity::nextSprite()
{
    this->spriteIndex++;
}

void Entity::setFriendly(bool friendly)
{
    this->friendly = friendly;
}