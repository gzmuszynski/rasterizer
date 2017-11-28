#include "light.h"

float4 light::getVector(float4 to)
{
    if(orig.w == 0)
        return dir;
    if(orig.w == 1)
        return float4(to, orig);
}

light light::operator*=(mat4 matrix)
{
    orig*=matrix;
    orig/=orig.w;

    dir*=matrix;
    dir/=dir.w;
    return *this;
}

light light::operator/=(float a)
{
    orig/=a;
    dir/=a;
    return *this;
}
