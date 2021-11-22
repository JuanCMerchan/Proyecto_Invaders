#include "timer.h"

Timer::Timer()
{
    reset();
}
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
void Timer::reset()
{
    timeval tv;
    gettimeofday(&tv, nullptr);
    tv.tv_sec -= OFFSET;
    this->start = tv.tv_sec * 1000;
    this->start += tv.tv_usec / 1000;
}