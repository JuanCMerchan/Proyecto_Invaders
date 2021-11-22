#include "player.h"

Bullet *Player::bullets;

Player::Player()
{

}

void Player::act(bool moveRight, bool moveLeft, bool shoot)
{
    if(this->alive)
    {
        switch (this->state)
        {
        case State::SHOOTING:
            if(moveRight)
            {
                this->moveRight();
            }
            if(moveLeft)
            {
                this->moveLeft();
            }
            if(shoot)
            {
                this->shoot();
                this->previousShot = this->timer.getMillis();
                this->state = State::WAITING;
            }
            if(this->health == 0)
            {
                this->state = State::DYING;
            }
            break;
            
        case State::WAITING:
            if(moveRight)
            {
                this->moveRight();
            }
            if(moveLeft)
            {
                this->moveLeft();
            }
            if(this->timer.getMillis() - previousShot > 1000)
            {
                this->state = State::SHOOTING;
            }
            if(this->health == 0)
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

void Player::initialize(int x, int y, const Sprites *sprites, Color color)
{
    Entity::initialize(x, y, sprites, color);
    this->health = 3;
    this->state = SHOOTING;
    this->friendly = true;
    this->timer.reset();
}

void Player::setBullets(Bullet *bullets)
{
    Player::bullets = bullets;
}

void Player::shoot()
{
    int x;
    int y;
    x = this->getX() + (this->getSprite()->width / 2);
    y = this->getY() - BULLET_SPRITE.length;
    y -= BULLET_SPRITE.length;
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        if (!(Player::bullets[i].getAlive()))
        {
            Player::bullets[i].reset(x, y, true);
            break;
        }
    }
}