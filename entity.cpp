#include "entity.h"

Entity::Entity()
{
    
}

/**************************************************************************
 *  Funcion: getAlive()
 *  Proposito: Obtener si la entidad esta viva o no
 *  Argumentos:
 *      void
 *  Retorno
 *      bool: Estado vital de la entidad
 *          false - muerto
 *          true -vivo
 * ***********************************************************************/
bool Entity::getAlive()
{
    return this->alive;
}


/**************************************************************************
 *  Funcion: getColor()
 *  Proposito: Obtener el color de la entidad
 *  Argumentos:
 *      void
 *  Retorno:
 *      Color: enumerador que representa el color de la entidad
 * ***********************************************************************/
Color Entity::getColor()
{
    return this->color;
}

/**************************************************************************
 *  Funcion: getFriendly()
 *  Proposito: Obtener si la entidad es amiga o enemiga
 *  Argumentos:
 *      void
 *  Retorno:
 *      bool:
 *          true - amiga
 *          false - enemiga
 * ***********************************************************************/
bool Entity::getFriendly()
{
    return this->friendly;
}

/**************************************************************************
 *  Funcion: getHealth()
 *  Proposito: Obtener la cantidad de vida de la entidad
 *  Argumentos:
 *      void
 *  Retorno:
 *      int: Cantidad de vida restante de la entidad
 * ***********************************************************************/
int Entity::getHealth()
{
    return this->health;
}

/**************************************************************************
 *  Funcion: getSprite()
 *  Proposito: Obtener el sprite e informacion relacionada de la entidad
 *  Argumentos:
 *      void
 *  Retorno:
 *      Sprites* - apuntador a la estructura Sprites asignada a la entidad
 * ***********************************************************************/
const Sprites *Entity::getSprite()
{
    return this->sprites;
}

/**************************************************************************
 *  Funcion: getSpriteIndex()
 *  Proposito: Obtener el indice del Sprite que mostrara la entidad en el
 *              momento actual
 *  Argumentos:
 *      void
 *  Retorno:
 *      int - Indice del sprite a mostrar
 * ***********************************************************************/
int Entity::getSpriteIndex()
{
    return spriteIndex;
}

/**************************************************************************
 *  Funcion: getX()
 *  Proposito: Obtener la posicion horizontal de la entidad
 *  Argumentos:
 *      void
 *  Retorno:
 *      int - Posicion horizontal de la entidad
 * ***********************************************************************/
int Entity::getX()
{
    return this->x;
}

/**************************************************************************
 *  Funcion: getY()
 *  Proposito: Obtener la posicion vertical de la entidad
 *  Argumentos:
 *      void
 *  Retorno:
 *      int - Posicion vertical de la entidad
 * ***********************************************************************/
int Entity::getY()
{
    return this->y;
}

/**************************************************************************
 *  Funcion: initialize()
 *  Proposito: Fijar los valores iniciales de la entidad
 *  Argumentos:
 *      x - Posicion horizontal
 *      y - Posicion vertical
 *      sprites - Apuntador a la estructura Sprites asignada
 *      color - Enumerador que representa el color de la entidad
 *  Retorno:
 *      void
 * ***********************************************************************/
void Entity::initialize(int x, int y, const Sprites *sprites, Color color)
{
    this->x = x;
    this->y = y;
    this->sprites = sprites;
    this->color = color;
    this->spriteIndex = 0;
    this->alive = true;
}

/**************************************************************************
 *  Funcion: loseHealth()
 *  Proposito: Reducir la vida de la entidad una unidad y cambiar su sprite
 *              al de explosion si su vida llega a 0
 *  Argumentos:
 *      void
 *  Retorno:
 *      void
 * ***********************************************************************/
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
