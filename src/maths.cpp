
#define _USE_MATH_DEFINES
#include "maths.h"
#include <math.h>

mat4 mat4::translate(float3 v)
{
    mat4 T = {{{1, 0, 0, v.x},
               {0, 1, 0, v.y},
               {0, 0, 1, v.z},
               {0, 0, 0, 1}}};
    return T;
}

mat4 mat4::scale(float3 v)
{
    mat4 S = {{{v.x, 0,   0,   0},
               {0,   v.y, 0,   0},
               {0,   0,   v.z, 0},
               {0,   0,   0,   1}}};
    return S;
}

mat4 mat4::rotate(float a, float3 v)
{
    float rad = M_PI/180;

    float s = std::sin(a*rad), c = std::cos(a*rad);

    v = v.normalize();

    mat4 R = {{{v.x*v.x*(1-c)+c    , v.x*v.y*(1-c)-v.z*s, v.x*v.z*(1-c)+v.y*s, 0},
               {v.x*v.y*(1-c)+v.z*s,  v.y*v.y*(1-c)+c   , v.z*v.y*(1-c)-v.x*s, 0},
               {v.x*v.z*(1-c)-v.y*s, v.z*v.y*(1-c)+v.x*s, v.z*v.z*(1-c)+c    , 0},
               {0                  , 0                  , 0                  , 1}}};

    mat4 Rz = {{{std::cos(v.z*rad), -std::sin(v.z*rad), 0, 0},
                {std::sin(v.z*rad),  std::cos(v.z*rad), 0, 0},
                {0             , 0            , 1, 0},
                {0             , 0            , 0, 1}}};

    mat4 Ry = {{{ std::cos(v.y*rad), 0, std::sin(v.y*rad), 0},
                {0             , 1, 0            , 0},
                {-std::sin(v.y*rad), 0, std::cos(v.y*rad), 0},
                {0             , 0, 0            , 1}}};

    mat4 Rx = {{{1, 0            , 0             , 0},
                {0, std::cos(v.x*rad), -std::sin(v.x*rad), 0},
                {0, std::sin(v.x*rad),  std::cos(v.x*rad), 0},
                {0, 0            , 0             , 1}}};
    return R;
}

mat4 mat4::lookAt(float3 up, float3 eye, float3 target)
{
    mat4 mat;
    return mat;
}

mat4 mat4::perspective(float fov, float ratio, float near, float far)
{
    mat4 mat;
    return mat;
}

mat4 mat4::operator*(mat4 N)
{
    mat4 M;

    M.mat[0][0] = mat[0][0]*N.mat[0][0] + mat[1][0]*N.mat[0][1] + mat[2][0]*N.mat[0][2] + mat[3][0]*N.mat[0][3];
    M.mat[0][1] = mat[0][1]*N.mat[0][0] + mat[1][1]*N.mat[0][1] + mat[2][1]*N.mat[0][2] + mat[3][1]*N.mat[0][3];
    M.mat[0][2] = mat[0][2]*N.mat[0][0] + mat[1][2]*N.mat[0][1] + mat[2][2]*N.mat[0][2] + mat[3][2]*N.mat[0][3];
    M.mat[0][3] = mat[0][3]*N.mat[0][0] + mat[1][3]*N.mat[0][1] + mat[2][3]*N.mat[0][2] + mat[3][3]*N.mat[0][3];

    M.mat[1][0] = mat[0][0]*N.mat[1][0] + mat[1][0]*N.mat[1][1] + mat[2][0]*N.mat[1][2] + mat[3][0]*N.mat[1][3];
    M.mat[1][1] = mat[0][1]*N.mat[1][0] + mat[1][1]*N.mat[1][1] + mat[2][1]*N.mat[1][2] + mat[3][1]*N.mat[1][3];
    M.mat[1][2] = mat[0][2]*N.mat[1][0] + mat[1][2]*N.mat[1][1] + mat[2][2]*N.mat[1][2] + mat[3][2]*N.mat[1][3];
    M.mat[1][3] = mat[0][3]*N.mat[1][0] + mat[1][3]*N.mat[1][1] + mat[2][3]*N.mat[1][2] + mat[3][3]*N.mat[1][3];

    M.mat[2][0] = mat[0][0]*N.mat[2][0] + mat[1][0]*N.mat[2][1] + mat[2][0]*N.mat[2][2] + mat[3][0]*N.mat[2][3];
    M.mat[2][1] = mat[0][1]*N.mat[2][0] + mat[1][1]*N.mat[2][1] + mat[2][1]*N.mat[2][2] + mat[3][1]*N.mat[2][3];
    M.mat[2][2] = mat[0][2]*N.mat[2][0] + mat[1][2]*N.mat[2][1] + mat[2][2]*N.mat[2][2] + mat[3][2]*N.mat[2][3];
    M.mat[2][3] = mat[0][3]*N.mat[2][0] + mat[1][3]*N.mat[2][1] + mat[2][3]*N.mat[2][2] + mat[3][3]*N.mat[2][3];

    M.mat[3][0] = mat[0][0]*N.mat[3][0] + mat[1][0]*N.mat[3][1] + mat[2][0]*N.mat[3][2] + mat[3][0]*N.mat[3][3];
    M.mat[3][1] = mat[0][1]*N.mat[3][0] + mat[1][1]*N.mat[3][1] + mat[2][1]*N.mat[3][2] + mat[3][1]*N.mat[3][3];
    M.mat[3][2] = mat[0][2]*N.mat[3][0] + mat[1][2]*N.mat[3][1] + mat[2][2]*N.mat[3][2] + mat[3][2]*N.mat[3][3];
    M.mat[3][3] = mat[0][3]*N.mat[3][0] + mat[1][3]*N.mat[3][1] + mat[2][3]*N.mat[3][2] + mat[3][3]*N.mat[3][3];

    return M;
}



float3 float3::operator*=(mat4 matrix)
{
    float xt = x, yt = y, zt = z;
    x = (matrix.mat[0][0]*xt) + (matrix.mat[0][1]*yt) + (matrix.mat[0][2]*zt) + (matrix.mat[0][3]);
    y = (matrix.mat[1][0]*xt) + (matrix.mat[1][1]*yt) + (matrix.mat[1][2]*zt) + (matrix.mat[1][3]);
    z = (matrix.mat[2][0]*xt) + (matrix.mat[2][1]*yt) + (matrix.mat[2][2]*zt) + (matrix.mat[2][3]);
    return *this;
}

float3 float3::normalize()
{
    float length = len();
    if(length!=0)
    {
        x/=length;
        y/=length;
        z/=length;
    }
    return *this;
}

float float3::len()
{
    return std::sqrt(x*x+y*y+z*z);
}
