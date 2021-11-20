#include "myRandom.h"

int myRandom::getRandomNumber(int max)
{
    return rand() % max;
}

void myRandom::setRandomSeed()
{
    srand(time(0));
}