#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include <stdio.h>
#include <cstdlib>
float GetRandomFloat()
{
    float r = static_cast<float>(rand()) / static_cast <float> (RAND_MAX);
    return r;
}
float randf()
{
    return GetRandomFloat();
}
int GetRandomInt()
{
    int r = rand() % 65535 - 32767;
    return r;
}
int randi()
{
    return GetRandomInt();
}


#define SEXY_MATH_IMPLEMENTATION
#include "../sexymathlibrary.h"

#include "vectortests.cpp"
#include "matrixtests.cpp"
#include "quaterniontests.cpp"
#include "advancedtests.cpp"
#include "practicaltests.cpp"
