#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "light.h"
#include "color.h"
#include <string>
#include <vector>

/*        B
 *       /\
 *      /  \
 *  AB /    \ BC
 *    /      \
 *   /________\
 *  A    AC    C
 */



struct vertex
{
    vertex(double x, double y, double z): pos(x,y,z) { }
    float4 pos;
    float4 norm;
    float4 uv;
    color  col;
};

struct hit{
    bool isHit;
    float4 areas;
};

struct triangle
{
    vertex *A,*B,*C;

    triangle(vertex *A, vertex *B, vertex *C);
    hit intersection(double x, double y);

};



#endif // TRIANGLE_H
