#pragma once

#include <random>
#include <time.h>

class Random
{
public:
  Random()
  {
    srand(time(NULL));
  }
  
  float GetRand(int min, int max)
  {
    return rand() % (max - min + 1) + min;
  }
};
