#ifndef MATH_H
#define MATH_H
#include <cmath>
#include <algorithm>

#endif // MATH_H

struct mat4;

struct float4
{
    float4() { }
    float4(float x, float y, float z) : x(x), y(y), z(z), w(1){ }
    float4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w){ }
    float4(float4 u, float4 v) : float4(v.x-u.x, v.y-u.y, v.z-u.z) { }
    float x,y,z,w;

    float4       operator*=(mat4 matrix);
    float4       operator*(float a);
    float4       operator+(float4 v);
    float4       operator*(float4 v);
    float const &operator[](int i) const;
    float       &operator[](int i);
    float4       operator-();
    float4       operator/=(float a);

    float4 normalize();
    static float4 crossProduct(float4 u, float4 v);
    static float dotProduct(float4 u, float4 v);

    float len();
    float len2();


    float invSqrt(float n); // Quake provided
};

struct mat4{
    float mat[4][4];

    static mat4 identity() {mat4 s = {{{1, 0, 0, 0},
                {0, 1, 0, 0},
                {0, 0, 1, 0},
                {0, 0, 0, 1}}}; return s;}

    mat4 operator*(mat4 N);
    mat4 transpose();
    mat4 inverse();

};
