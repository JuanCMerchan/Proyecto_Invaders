#include "timer.h"

Timer::Timer()
{
    reset();
}

/**************************************************************************
 *  Funcion: getMillis()
 *  Proposito: Retornar la cantidad de milisegundos transcurridos desde el
 *             ultimo reinicio de un objeto Timer
 *  Argumentos:
 *      void
 *  Retorno:
 *      unsigned long - Numero de milisegundos transcurridos
 * ***********************************************************************/
unsigned long Timer::getMillis()
{
    timeval tv;
    unsigned long millis;
    gettimeofday(&tv, nullptr);
    tv.tv_sec -= OFFSET;
    millis = tv.tv_sec * 1000;
    millis += tv.tv_usec / 1000;
    millis -= this->start;
    return millis;
}

/**************************************************************************
 *  Funcion: reset()
 *  Proposito: Guarda en el atributo start los milisegundos transcurridos
 *             desde Epoch menos un offset
 *  Argumentos:
 *      void
 *  Retorno:
 *      void
 * ***********************************************************************/
void Timer::reset()
{
    timeval tv;
    gettimeofday(&tv, nullptr);
    tv.tv_sec -= OFFSET;
    this->start = tv.tv_sec * 1000;
    this->start += tv.tv_usec / 1000;
}