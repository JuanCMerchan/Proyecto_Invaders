#include "ufo.h"
#include "display.h"

Bullet *Ufo::bullets;

Ufo::Ufo()
{
}

/**************************************************************************
 *  Funcion: act()
 *  Proposito: Funcion tipo maquina de estado que define el comportamiento
 *             del ovni
 *  Argumentos:
 *      void
 *  Retorno:
 *      void
 * ***********************************************************************/
void Ufo::act()
{
    switch (this->state)
    {
    case State::MOVING_RIGHT:
        if (this->x >= DISP_WIDTH) 
        {
            //Si el ovni se sale de la pantalla pasa al respectivo estado de espera y se actualiza el valor de previous
            this->state = State::WAITING_RIGHT;
            this->previous = this->timer.getMillis();
        }
        else
        {
            if (!this->shot)
            {
                if (this->x >= this->player->getX() + 1 && this->x <= this->player->getX() + this->player->getSprite()->length - 1)
                {
                    //Si el ovni no ha disparado y esta encima del jugador procede a disparar y marca shot como true
                    shoot();
                    this->shot = true;
                }
            }
            moveRight(); //El ovni se mueve hacia la derecha
        }
        if (this->health == 0)
        {
            this->state = State::DYING;
        }
        break;

    case State::MOVING_LEFT:
        if (this->x <= 0 - this->sprites->width)
        {
            //Si el ovni se sale de la pantalla pasa al respectivo estado de espera y se actualiza el valor de previous
            this->state = State::WAITING_LEFT;
            this->previous = this->timer.getMillis();
        }
        else
        {
            if (!this->shot)
            {
                if (this->x >= this->player->getX() + 1 && this->x <= this->player->getX() + this->player->getSprite()->length - 1)
                {
                    //Si el ovni no ha disparado y esta encima del jugador procede a disparar y marca shot como true
                    shoot();
                    this->shot = true;
                }
            }
            moveLeft(); //El ovni se mueve hacia la izquierda
        }
        if (this->getHealth() == 0)
        {
            //Si el ovni tiene 0 de vida pasa el estado de morir y se actualiza el valor de previous
            this->state = State::DYING;
            this->previous = this->timer.getMillis();
        }
        break;

    case State::WAITING_LEFT:
        if (this->timer.getMillis() - this->previous >= UFO_CD)
        {
            //El ovni espera hasta que se supere su tiempo de enfriamiento y pasa al respectivo estado de movimiento
            //tambien se pasa shot a false
            this->state = State::MOVING_RIGHT;
            this->shot = false;
        }
        break;

    case State::WAITING_RIGHT:
        if (this->timer.getMillis() - this->previous >= UFO_CD)
        {
            //El ovni espera hasta que se supere su tiempo de enfriamiento y pasa al respectivo estado de movimiento
            //tambien se pasa shot a false
            this->state = State::MOVING_LEFT;
            this->shot = false;
        }
        break;

    case DYING:
        //El ovni llama a su funcion reset y pasa al estado de espera en la izquierda y se actualiza el valor de previous
        reset();
        this->state = State::WAITING_LEFT;
        this->previous = timer.getMillis();
        break;
    default:
        break;
    }
}

/**************************************************************************
 *  Funcion: getScore()
 *  Proposito: Obtener el score asignado al ovni
 *  Argumentos:
 *      void
 *  Retorno:
 *      int - Puntaje asignado al ovni
 * ***********************************************************************/
int Ufo::getScore()
{
    return this->score;
}

/**************************************************************************
 *  Funcion: initialize()
 *  Proposito: Fijar los valores iniciales de los atributos del ovni
 *  Argumentos:
 *      color - Enumerador que representa el color de la entidad
 *  Retorno:
 *      void
 * ***********************************************************************/
void Ufo::initialize(Color color)
{
    Entity::initialize(0 - UFO_SPRITE.width, 4, &UFO_SPRITE, color);
    this->health = 1;
    this->alive = true;
    this->friendly = false;
    this->state = State::WAITING_LEFT;
    this->shot = false;
    this->score = UFO_SCORE;
}

/**************************************************************************
 *  Funcion: moveRight()
 *  Proposito: Incrementar la posicion horizontal del ovni una cantidad de
 *             unidades predeterminada
 *  Argumentos: 
 *      void
 *  Retorno:
 *      void
 * ***********************************************************************/
void Ufo::moveRight()
{
    this->x += 2;
}

/**************************************************************************
 *  Funcion: moveLeft()
 *  Proposito: Reducir la posicion horizontal del ovni una cantidad de
 *             unidades predeterminada
 *  Argumentos: 
 *      void
 *  Retorno:
 *      void
 * ***********************************************************************/
void Ufo::moveLeft()
{
    this->x -= 2;
}

/**************************************************************************
 *  Funcion: reset()
 *  Proposito: Reinicia los atributos del ovni a los valores especificados
 *  Argumentos: 
 *      void
 *  Retorno:
 *      void
 * ***********************************************************************/
void Ufo::reset()
{
    this->x = 0 - UFO_SPRITE.width;
    this->health = 1;
    this->alive = true;
    this->shot = false;
    this->sprites = &UFO_SPRITE;
}

/**************************************************************************
 *  Funcion: setBullets()
 *  Proposito: Permitir que el ovni tenga una referencia al arreglo de
 *             balas del juego
 *  Argumentos: 
 *      bullets - Apuntador al arreglo de balas
 *  Retorno:
 *      void
 * ***********************************************************************/
void Ufo::setBullets(Bullet *bullets)
{
    Ufo::bullets = bullets;
}

/**************************************************************************
 *  Funcion: setPlayer()
 *  Proposito: Permitir que el ovni tenga una referencia al jugador
 *  Argumentos: 
 *      player - Apuntador al jugador
 *  Retorno:
 *      void
 * ***********************************************************************/
void Ufo::setPlayer(Entity *player)
{
    this->player = player;
}

/**************************************************************************
 *  Funcion: shoot()
 *  Proposito: Dispapar una bala enemiga desde la parte inferior del ovni
 *  Argumentos:
 *      void
 *  Retorno:
 *      void
 * ***********************************************************************/
void Ufo::shoot()
{
    int x;
    int y;
    x = this->getX() + (this->getSprite()->width / 2);
    y = this->getY() + this->getSprite()->length;
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        if (!(Ufo::bullets[i].getAlive()))
        {
            Ufo::bullets[i].reset(x, y, false);
            break;
        }
    }
}