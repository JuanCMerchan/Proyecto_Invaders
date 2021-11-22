#include "bullet.h"

Entity *Bullet::entities[MAX_ENTITIES];
int Bullet::sizeEntities;

Bullet::Bullet()
{
}

/**************************************************************************
 *  Funcion: act()
 *  Proposito: Funcion tipo maquina de estados que define el comportamiento
 *             de una bala
 *  Argumentos:
 *      void
 *  Retorno:
 *      void
 * ***********************************************************************/
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

/**************************************************************************
 *  Funcion: checkCollisions()
 *  Proposito: Revisar si la bala esta colisionando con alguna de las otras
 *             entidades del juego. Si la bala es enemiga solo colisiona
 *             contra entidades amigas mientras que si es amiga puede
 *             colisionar contra cualquier entidad. Si exite colision
 *             las entidades colisionando pierden vida.
 *  Argumentos:
 *      void
 *  Retorno:
 *      void
 * ***********************************************************************/
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

/**************************************************************************
 *  Funcion: initialize()
 *  Proposito: Fijar los valores iniciales de los atributos de la bala
 *  Argumentos:
 *      x - Posicion horizontal
 *      y - Posicion vertical
 *      color - Enumerador que representa el color de la entidad
 *  Retorno:
 *      void
 * ***********************************************************************/
void Bullet::initialize(int x, int y, Color color)
{
    Entity::initialize(x, y, &BULLET_SPRITE, color);
    this->health = 1;
    this->alive = false;
    this->timeAlive = 0;
}

/**************************************************************************
 *  Funcion: isColliding()
 *  Proposito: Revisar si la bala esta colisionando con una entidad
 *  Argumentos:
 *      entity - Apuntador a la entidad con la que se quiere ver si existe
 *               colision
 *  Retorno:
 *      bool:
 *          true - Existe colision
 *          false - No existe colision
 * ***********************************************************************/
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

/**************************************************************************
 *  Funcion: moveDown()
 *  Proposito: Incrementar la posicion vertical de la bala una cantidad de
 *             unidades predeterminada
 *  Argumentos: 
 *      void
 *  Retorno:
 *      void
 * ***********************************************************************/
void Bullet::moveDown()
{
    this->y += 2;
}

/**************************************************************************
 *  Funcion: moveDown()
 *  Proposito: Reducir la posicion vertical de la bala una cantidad de
 *             unidades predeterminada
 *  Argumentos: 
 *      void
 *  Retorno:
 *      void
 * ***********************************************************************/
void Bullet::moveUp()
{
    this->y -= 2;
}

/**************************************************************************
 *  Funcion: reset()
 *  Proposito: Reiniciar los valores de la bala al ser disparada
 *  Argumentos:
 *      x - Posicion horizontal
 *      y - Posicion vertical
 *      friendly - Booleano que describe se es amiga o enemiga
 *  Retorno:
 *      void
 * ***********************************************************************/
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

/**************************************************************************
 *  Funcion: setEntities()
 *  Proposito: Permitir que la clase Bala tenga una referencia a las
 *             entidades del juego con el proposito de poder interactuar
 *             con ellas 
 *  Argumentos:
 *      entities - Arreglo de apuntadores a las entidades
 *  Retorno:
 *      void
 * ***********************************************************************/
void Bullet::setEntities(Entity *entities[MAX_ENTITIES])
{
    for (int i = 0; i < MAX_ENTITIES; i++)
    {
        Bullet::entities[i] = entities[i];
    }
}