#pragma once

#include <sys/time.h>

#define OFFSET 1636000000L

class Timer
{
private:
    unsigned long start;
public:
    Timer();
    unsigned long getMillis();
    void reset();
};
