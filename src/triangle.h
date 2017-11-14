#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "maths.h"
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
    vertex(float x, float y, float z): pos(x,y,z) { }
    float3 pos;
    float3 norm;
    float3 uv;
    color  col;

    vertex operator*=(mat4 matrix);
};

struct hit{
    bool isHit;
    float3 areas;
};

struct triangle
{
    vertex *A,*B,*C;

    triangle(vertex *A, vertex *B, vertex *C);
    hit intersection(float x, float y);
};

std::vector<std::string> split(std::string string, char separator);


#endif // TRIANGLE_H
