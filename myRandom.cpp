#include "myRandom.h"

/**************************************************************************
 *  Funcion: getRandomNumber()
 *  Proposito: Retorna un numero pseudorandom con un maximo excluyente
 *  Argumentos:
 *      max - Maximo excluyente del numero retornado
 *  Retorno:
 *      int - Numero random
 * ***********************************************************************/
int myRandom::getRandomNumber(int max)
{
    return rand() % max;
}

/**************************************************************************
 *  Funcion: setRandomSeed
 *  Proposito: Cambia la seed para la generacion de numeros random usando
 *             el tiempo unix
 *  Argumentos:
 *      void
 *  Retorno:
 *      void
 * ***********************************************************************/
void myRandom::setRandomSeed()
{
    srand(time(0));
}