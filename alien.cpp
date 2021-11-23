#include "alien.h"

Bullet *Alien::bullets;

Alien::Alien()
{
}

/**************************************************************************
 *  Funcion: act()
 *  Proposito: Funcion tipo maquina de estado que define el comportamiento
 *              de un alien
 *  Argumentos:
 *      void
 *  Retorno:
 *      void
 * ***********************************************************************/
void Alien::act()
{
    if (this->alive)
    {
        switch (this->state)
        {
        case State::MOVING_RIGHT:
            if (this->movement == MAX_MOVEMENT)
            {
                //Si el alien llega al maximo de su movimiento se mueve una vez hacia abajo y cambia a moverse en la otra direccion
                moveDown();
                this->state = MOVING_LEFT;
            }
            else
            {
                //El alien se mueve e incrementa el valor de su movimiento
                moveRight();
                this->movement++;
            }
            if (myRandom::getRandomNumber(CHANCE_SHOOT) == 1)
            {
                //Se genera un numero al azar y si este da uno el alien dispara
                shoot();
            }
            if (this->health == 0)
            {
                //Si la vida del alien esta en 0 pasa al estado de morir
                this->state = State::DYING;
            }
            break;

        case State::MOVING_LEFT:
            if (this->movement == 1)
            {
                //Si el alien llega al maximo de su movimiento se mueve una vez hacia abajo y cambia a moverse en la otra direccion
                moveDown();
                this->state = MOVING_RIGHT;
            }
            else
            {
                //El alien se mueve e incrementa el valor de su movimiento
                moveLeft();
                this->movement--;
            }
            if (myRandom::getRandomNumber(CHANCE_SHOOT) == 1)
            {
                //Se genera un numero al azar y si este da uno el alien dispara
                shoot();
            }
            if (this->health == 0)
            {
                //Si la vida del alien esta en 0 pasa al estado de morir
                this->state = State::DYING;
            }
            break;

        case State::DYING:
            //Se pasa alive a falso
            this->alive = false;
            break;
        default:
            break;
        }
        //Cada ciclo el sprite del alien pasa al siguiente
        this->spriteIndex++;
        this->spriteIndex %= this->sprites->numFrames;
    }
}

/**************************************************************************
 *  Funcion: initialize()
 *  Proposito: Fijar los valores iniciales de los atributos del alien
 *  Argumentos:
 *      x - Posicion horizontal
 *      y - Posicion vertical
 *      sprites - Apuntador a la estructura Sprites asignada
 *      color - Enumerador que representa el color de la entidad
 *      score - Puntaje asignado al alien
 *  Retorno:
 *      void
 * ***********************************************************************/
void Alien::initialize(int x, int y, const Sprites *sprites, Color color, int score)
{
    Entity::initialize(x, y, sprites, color);
    this->health = 1;
    this->movement = 0;
    this->state = State::MOVING_RIGHT;
    this->score = score;
}

/**************************************************************************
 *  Funcion: getScore()
 *  Proposito: Obtener el puntaje asignado al alien
 *  Argumentos:
 *      void
 *  Retorno:
 *      int - Puntaje que vale el alien
 * ***********************************************************************/
int Alien::getScore()
{
    return this->score;
}

/**************************************************************************
 *  Funcion: moveDown()
 *  Proposito: Incrementar la posicion vertical del alien una cantidad de
 *              unidades predeterminada
 *  Argumentos: 
 *      void
 *  Retorno:
 *      void
 * ***********************************************************************/
void Alien::moveDown()
{
    this->y += 8;
}

/**************************************************************************
 *  Funcion: moveLeft()
 *  Proposito: Reducir la posicion horizontal del alien una cantidad de
 *              unidades predeterminada
 *  Argumentos: 
 *      void
 *  Retorno:
 *      void
 * ***********************************************************************/
void Alien::moveLeft()
{
    this->x -= 2;
}

/**************************************************************************
 *  Funcion: moveUp()
 *  Proposito: Reducir la posicion vertical del alien una cantidad de
 *              unidades predeterminada
 *  Argumentos: 
 *      void
 *  Retorno:
 *      void
 * ***********************************************************************/
void Alien::moveUp()
{
    this->y -= 2;
}

/**************************************************************************
 *  Funcion: moveRight()
 *  Proposito: Incrementar la posicion horizontal del alien una cantidad de
 *              unidades predeterminada
 *  Argumentos: 
 *      void
 *  Retorno:
 *      void
 * ***********************************************************************/
void Alien::moveRight()
{
    this->x += 2;
}

/**************************************************************************
 *  Funcion: setBullets()
 *  Proposito: Permitir que el alien tenga una referencia a la lista de 
 *              balas del juego
 *  Argumentos:
 *      bullets - Apuntador a un arreglo de balas
 *  Retorno:
 *      void
 * ***********************************************************************/
void Alien::setBullets(Bullet *bullets)
{
    Alien::bullets = bullets;
}

/**************************************************************************
 *  Funcion: shoot()
 *  Proposito: Dispapar una bala enemiga desde la parte inferior del alien
 *  Argumentos:
 *      void
 *  Retorno:
 *      void
 * ***********************************************************************/
void Alien::shoot()
{
    int x;
    int y;
    x = this->getX() + (this->getSprite()->width / 2);
    y = this->getY() + this->getSprite()->length;
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        if (!(Alien::bullets[i].getAlive()))
        {
            Alien::bullets[i].reset(x, y, false);
            break;
        }
    }
}