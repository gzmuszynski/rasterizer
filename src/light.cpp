#define _USE_MATH_DEFINES
#include "light.h"
#include "cmath"

float4 light::getVector(float4 to)
{
    if(orig.w == 0)
        return dir;
    if(orig.w == 1)
        return float4(to, orig);
}

float light::getAttenuation(float4 vec)
{
    if(orig.w == 0)
        return 1.0f;
    if(orig.w == 1)
    {
        float dist = vec.len2();

        float attenuation = 1.0f / (1.0f  + (dist * this->attenuation));

        if(cutoff == 0)
            return attenuation;

        float DdotVangle = float4::dotProduct(dir.normalize(),-vec.normalize());

        if(DdotVangle < (90 - cutoff )* M_PI/180)
            return 0.0f;

        return std::max(0.0f, std::pow(DdotVangle, exp) * attenuation);

    }
}

