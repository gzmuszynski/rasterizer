#ifndef LIGHT_H
#define LIGHT_H
#include "color.h"

struct light
{
    light(float4 orig, float4 dir) : orig(orig), dir(dir) { }
    float4 orig;
    float4 dir;

    color ambient;
    color diffuse;
    color specular;

    float attenuation = 0.0f;

    float4 getVector(float4 to);
};

#endif // LIGHT_H
