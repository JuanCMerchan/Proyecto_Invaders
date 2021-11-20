#include "bunker.h"

Bunker::Bunker()
{

}

void Bunker::act()
{
    if(this->alive)
    {
        switch (this->state)
        {
        case State::EXISTING:
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

void Bunker::initialize(int x, int y, const Sprites *sprites, Color color)
{
    Entity::initialize(x, y, sprites, color);
    this->health = 4;
    this->friendly = true;
    this->state = State::EXISTING;
}
