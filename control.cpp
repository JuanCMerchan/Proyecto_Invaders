#include "control.h"

Control::Control()
{
}

/**************************************************************************
 *  Funcion: initialize
 *  Proposito: Fijar los valores de los atributos de la terminal de linux
 *             para el correcto funcionamiento de la lectura de inputs
 *  Argumentos:
 *      void
 *  Retorno:
 *      void
 * ***********************************************************************/
void Control::initialize()
{
    tcgetattr(STDIN_FILENO, &(this->oldt));
    this->newt = this->oldt;
    this->newt.c_lflag &= ~(ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &(this->newt));
}

/**************************************************************************
 *  Funcion: deInitialize()
 *  Proposito: Retornar los atributos de la terminal de linux
 *             a sus valores originales
 *  Argumentos:
 *      void
 *  Retorno:
 *      void
 * ***********************************************************************/
void Control::deInitialize()
{
    tcsetattr(STDIN_FILENO, TCSANOW, &(this->oldt));
}

/**************************************************************************
 *  Funcion: getKeyPresses()
 *  Proposito: Detectar las teclas presionadas y cambiar los valores de    
 *             moveLeft, moveRight y shoot si sus respectivas teclas estan
 *             siendo presionadas.
 *  Argumentos:
 *      void
 *  Retorno:
 *      void
 * ***********************************************************************/
void Control::getKeyPresses()
{
    char keyPressed;
    this->moveLeft = false;
    this->moveRight = false;
    this->shoot = false;
    this->tv.tv_sec = 0;
    this->tv.tv_usec = 5;

    FD_ZERO(&rdfs);
    FD_SET(STDIN_FILENO, &(this->rdfs));
    select(STDIN_FILENO + 1, &(this->rdfs), NULL, NULL, &tv);
    do
    {
        keyPressed = 0;
        if (FD_ISSET(STDIN_FILENO, &(this->rdfs)))
        {
            keyPressed = getchar();
            switch (keyPressed)
            {
            case 'j':
                this->moveLeft = true;
                break;
            case 'l':
                this->moveRight = true;
                break;
            case 'i':
                this->shoot = true;
                break;
            default:
                break;
            }
            select(STDIN_FILENO + 1, &(this->rdfs), NULL, NULL, &tv);
        }
    }while(keyPressed);
    fflush(stdin);
}

/**************************************************************************
 *  Funcion: getMoveLeft()
 *  Proposito: Obtener el valor del atributo moveLeft
 *  Argumentos:
 *      void
 *  Retorno:
 *      bool:
 *          true - El usuario desea moverse a la izquierda
 *          false - El usuario no desea moverse a la izquierda
 * ***********************************************************************/
bool Control::getMoveLeft()
{
    return moveLeft;
}

/**************************************************************************
 *  Funcion: getMoveRight()
 *  Proposito: Obtener el valor del atributo moveRight
 *  Argumentos:
 *      void
 *  Retorno:
 *      bool:
 *          true - El usuario desea moverse a la derecha
 *          false - El usuario no desea moverse a la derecha
 * ***********************************************************************/
bool Control::getMoveRight()
{
    return moveRight;
}

/**************************************************************************
 *  Funcion: getShoot()
 *  Proposito: Obtener el valor del atributo Shoot
 *  Argumentos:
 *      void
 *  Retorno:
 *      bool:
 *          true - El usuario desea disparar
 *          false - El usuario no desea disparar
 * ***********************************************************************/
bool Control::getShoot()
{
    return shoot;
}
