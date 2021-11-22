#include "actor.h"

Actor::Actor()
{

}

/**************************************************************************
 *  Funcion: moveDown()
 *  Proposito: Incrementar la posicion vertical del actor una unidad
 *  Argumentos: 
 *      void
 *  Retorno:
 *      void
 * ***********************************************************************/
void Actor::moveDown()
{
    this->y++;
}

/**************************************************************************
 *  Funcion: moveLeft()
 *  Proposito: Reducir la posicion horizontal del actor una unidad
 *  Argumentos: 
 *      void
 *  Retorno:
 *      void
 * ***********************************************************************/
void Actor::moveLeft()
{
    this->x--;
}

/**************************************************************************
 *  Funcion: moveUp()
 *  Proposito: Reducir la posicion vertical del actor una unidad
 *  Argumentos: 
 *      void
 *  Retorno:
 *      void
 * ***********************************************************************/
void Actor::moveUp()
{
    this->y--;
}

/**************************************************************************
 *  Funcion: moveRight()
 *  Proposito: Incrementar la posicion horizontal del actor una unidad
 *  Argumentos: 
 *      void
 *  Retorno:
 *      void
 * ***********************************************************************/
void Actor::moveRight()
{
    this->x++;
}

/**************************************************************************
 *  Funcion:
 *  Proposito:
 *  Argumentos:
 *  Retorno:
 * ***********************************************************************/