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

    float4 getVector(float4 to);

    light operator*=(mat4 matrix);
    light operator/=(float a);
};

#endif // LIGHT_H
