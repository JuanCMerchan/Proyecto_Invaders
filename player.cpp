#include "player.h"

Bullet *Player::bullets;

Player::Player()
{

}

/**************************************************************************
 *  Funcion: act()
 *  Proposito: Funcion tipo maquina de estados que define el comportamiento
 *             del jugador
 *  Argumentos:
 *      moveRight - Si el jugador se debe mover a la derecha
 *      moveLeft - Si el jugadors se debe mover a la izquierda
 *      shoot - Si el jugador debe disparar
 *  Retorno:
 *      void
 * ***********************************************************************/
void Player::act(bool moveRight, bool moveLeft, bool shoot)
{
    if(this->alive)
    {
        switch (this->state)
        {
        case State::SHOOTING:
            if(moveRight)
            {
                //Si la directris de moverse a la derecha es verdadera el jugador se mueve a la derecha
                this->moveRight();
            }
            if(moveLeft)
            {
                //Si la directris de moverse a la izquierda es verdadera el jugador se mueve a la izquierda
                this->moveLeft();
            }
            if(shoot)
            {
                //Si la directris de disparar es verdadera el jugador dispara, se actualiza previousShot y se pasa al estado de espera
                this->shoot();
                this->previousShot = this->timer.getMillis();
                this->state = State::WAITING;
            }
            if(this->health == 0)
            {
                //Si la vida del jugador llega a 0 pasa al estado de morir
                this->state = State::DYING;
            }
            break;
            
        case State::WAITING:
            if(moveRight)
            {
                //Si la directris de moverse a la derecha es verdadera el jugador se mueve a la derecha
                this->moveRight();
            }
            if(moveLeft)
            {
                //Si la directris de moverse a la izquierda es verdadera el jugador se mueve a la izquierda
                this->moveLeft();
            }
            if(this->timer.getMillis() - previousShot > SHOOT_CD)
            {
                //Si se cumplio al tiempo de espera el jugador vuelve al estado de disparar
                this->state = State::SHOOTING;
            }
            if(this->health == 0)
            {
                //Si la vida del jugador llega a 0 pasa al estado de morir
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
 *  Proposito: Fijar los valores iniciales de los atributos del jugador
 *  Argumentos:
 *      x - Posicion horizontal
 *      y - Posicion vertical
 *      color - Enumerador que representa el color de la entidad
 *  Retorno:
 *      void
 * ***********************************************************************/
void Player::initialize(int x, int y, Color color)
{
    Entity::initialize(x, y, &PLAYER_SPRITE, color);
    this->health = 3;
    this->state = SHOOTING;
    this->friendly = true;
    this->timer.reset();
}

/**************************************************************************
 *  Funcion: setBullets
 *  Proposito: Permitir que el jugador tenga una referencia a la lista de
 *             balas del juego
 *  Argumentos:
 *      bullets - Apuntador al arreglo de balas
 *  Retorno:
 *      void
 * ***********************************************************************/
void Player::setBullets(Bullet *bullets)
{
    Player::bullets = bullets;
}

/**************************************************************************
 *  Funcion: shoot()
 *  Proposito: Disparar una bala amiga desde la posicion arriba del jugador
 *  Argumentos:
 *      void
 *  Retorno:
 *      void
 * ***********************************************************************/
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