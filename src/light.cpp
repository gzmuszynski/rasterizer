#define _USE_MATH_DEFINES
#include "light.h"
#include "cmath"

float4 light::getVector(float4 to)
{
        return float4(to, orig);
}
