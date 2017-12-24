#ifndef LIGHT_H
#define LIGHT_H
#include "color.h"

struct light
{
    light(float4 orig, float4 dir) : orig(orig), dir(dir) { }
    float4 orig;
    float4 dir;
    float cutoff = 0.0f;
    float exp = 1.0f;

    color ambient;
    color diffuse;
    color specular;

    float attenuation = 0.0f;

    float4 getVector(float4 to);
    float getAttenuation(float4 vec);
};

#endif // LIGHT_H
