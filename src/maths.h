#ifndef MATH_H
#define MATH_H
#include "cmath"

#endif // MATH_H
struct mat4;

struct float4
{
    float4() { }
    float4(float x, float y, float z) : x(x), y(y), z(z), w(1){ }
    float4(float4 u, float4 v) : float4(v.x-u.x, v.y-u.y, v.z-u.z) { }
    float x,y,z,w;

    float4       operator*=(mat4 matrix);
    float const &operator[](int i) const;
    float       &operator[](int i);
    float4       operator-();
    float4       operator/=(float a);

    float4 normalize();
    static float4 crossProduct(float4 u, float4 v);
    static float dotProduct(float4 u, float4 v);
    float len();
};

struct mat4{
    float mat[4][4];

    static mat4 identity() {mat4 s = {{{1, 0, 0, 0},
                {0, 1, 0, 0},
                {0, 0, 1, 0},
                {0, 0, 0, 1}}}; return s;}

    static mat4 translate(float4 v);
    static mat4 scale(float4 v);
    static mat4 rotate(float a, float4 v);

    static mat4 lookAt(float4 up, float4 eye, float4 target);
    static mat4 perspective(float fov, float ratio, float near, float far);

    mat4 operator*(mat4 N);

};
