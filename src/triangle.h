#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "color.h"

/*        C
 *       /\
 *      /  \
 *  AC /    \ BC
 *    /      \
 *   /________\
 *  A    AB    B
 */


struct float3
{
    float x,y,z;
};

struct hit{
    bool isHit;
    float3 areas;
};

struct triangle
{
    float3 A,B,C;

    color colA;
    color colB;
    color colC;

    hit intersection(float x, float y);
};



#endif // TRIANGLE_H
