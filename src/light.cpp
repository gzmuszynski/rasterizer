#include "light.h"

float4 light::getVector(float4 to)
{
    if(orig.w == 0)
        return dir;
    if(orig.w == 1)
        return float4(to, orig);
}

