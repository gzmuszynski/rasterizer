#ifndef LIGHT_H
#define LIGHT_H
#include "color.h"

struct light
{
    light(float4 orig) : orig(orig){ }
    float4 orig;

    color ambient;
    color diffuse;
    color specular;

    float4 getVector(float4 to);
};

#endif // LIGHT_H
