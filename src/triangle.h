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
    vertex(float x, float y, float z): pos(x,y,z) { }
    float4 pos;
    float4 norm;
    float4 uv;
    color  col;

    vertex transform(mat4 matrix, mat4 matrixT);
    vertex operator/=(float a);
};

struct hit{
    bool isHit;
    float4 areas;
};

struct triangle
{
    vertex *A,*B,*C;

    triangle(vertex *A, vertex *B, vertex *C);
    hit intersection(float x, float y);

};

std::vector<std::string> split(std::string string, char separator);


#endif // TRIANGLE_H
