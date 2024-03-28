#include <GL/glut.h>
#include <cstdlib>
// #include "headers/stb_image.h"

#include <iostream>

int randint(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

bool randbool()
{
    return rand() % 2;
}

float randfloat(float min, float max)
{
    return (max - min) * ((float)rand() / RAND_MAX) + min;
}

int randRange(int negmin, int megmax, int posmin, int posmax)
{
    if (randbool())
    {
        return randint(negmin, megmax);
    }
    else
    {
        return randint(posmin, posmax);
    }
}

float min(float a, float b)
{
    return a <= b ? a : b;
}