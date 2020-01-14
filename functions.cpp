#include "functions.h"

float rnd(float a, float b)
{
    float r=rand()/(float)RAND_MAX;
    return a+r*(b-a);
}