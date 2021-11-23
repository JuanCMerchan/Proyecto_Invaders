#include "bunker.h"

Bunker::Bunker()
{

}

/**************************************************************************
 *  Funcion: act()
 *  Proposito: Funcion tipo maquina de estado que define el comportamiento
 *             de un bunker
 *  Argumentos:
 *      void
 *  Retorno:
 *      void
 * ***********************************************************************/
void Bunker::act()
{
    if(this->alive)
    {
        switch (this->state)
        {
        case State::EXISTING:
            if(this->health == 0)
            {
                //Si la vida del bunker llega a 0 se pasa al estado de morir
                this->state = State::DYING;
            }
            break;
        case State::DYING:
            //Se pasa alive a false
            this->alive = false;
            break;
        default:
            break;
        }
    }
}

/**************************************************************************
 *  Funcion: initialize()
 *  Proposito: Fijar los valores iniciales del bunker
 *  Argumentos:
 *      x - Posicion horizontal
 *      y - Posicion vertical
 *      color - Enumerador que representa el color de la entidad
 *  Retorno:
 *      void
 * ***********************************************************************/
void Bunker::initialize(int x, int y, Color color)
{
    Entity::initialize(x, y, &BUNKER_SPRITE, color);
    this->health = 4;
    this->friendly = true;
    this->state = State::EXISTING;
}

/**************************************************************************
 *  Funcion:
 *  Proposito:
 *  Argumentos:
 *  Retorno:
 * ***********************************************************************/