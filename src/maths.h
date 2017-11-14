#ifndef MATH_H
#define MATH_H
#include "cmath"

#endif // MATH_H
struct mat4;

struct float3
{
    float3() { }
    float3(float x, float y, float z) : x(x), y(y), z(z) { }
    float x,y,z;

    float3 operator*=(mat4 matrix);
    float3 normalize();
    float len();
};

struct mat4{
    float mat[4][4];

    static mat4 translate(float3 v);
    static mat4 scale(float3 v);
    static mat4 rotate(float a, float3 v);

    static mat4 lookAt(float3 up, float3 eye, float3 target);
    static mat4 perspective(float fov, float ratio, float near, float far);

    mat4 operator*(mat4 N);

};
