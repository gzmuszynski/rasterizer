
#define _USE_MATH_DEFINES
#include "maths.h"
#include <math.h>


mat4 mat4::translate(float4 v)
{
    mat4 T = {{{1, 0, 0, v.x},
               {0, 1, 0, v.y},
               {0, 0, 1, v.z},
               {0, 0, 0, 1}}};
    return T;
}

mat4 mat4::scale(float4 v)
{
    mat4 S = {{{v.x, 0,   0,   0},
               {0,   v.y, 0,   0},
               {0,   0,   v.z, 0},
               {0,   0,   0,   1}}};
    return S;
}

mat4 mat4::rotate(float a, float4 v)
{
    float rad = M_PI/180.0f;

    float s = std::sin(a*rad), c = std::cos(a*rad);

    v = v.normalize();

    mat4 R = {{{v.x*v.x*(1-c)+c    , v.x*v.y*(1-c)-v.z*s, v.x*v.z*(1-c)+v.y*s, 0},
               {v.x*v.y*(1-c)+v.z*s,  v.y*v.y*(1-c)+c   , v.z*v.y*(1-c)-v.x*s, 0},
               {v.x*v.z*(1-c)-v.y*s, v.z*v.y*(1-c)+v.x*s, v.z*v.z*(1-c)+c    , 0},
               {0                  , 0                  , 0                  , 1}}};

    return R;
}

mat4 mat4::lookAt(float4 up, float4 eye, float4 target)
{
    up = up.normalize();
    float4 forward = float4(eye,target).normalize();
    float4 right   = float4::crossProduct(up,forward).normalize();
           up      = float4::crossProduct(forward,right);

//    mat4 mat = {{{right.x, up.x,   -forward.x, 0},
//                 {right.y, up.y,   -forward.y, 0},
//                 {right.z, up.z,   -forward.z, 0},
//                 {-eye.x,  -eye.y, -eye.z,     1}}};
    mat4 Mov = {{{1, 0, 0, -eye.x},
                 {0, 1, 0, -eye.y},
                 {0, 0, 1, -eye.z},
                 {0, 0, 0, 1}}};

    mat4 Rot = {{{right.x,    right.y,    right.z,    0},
                 {up.x,       up.y,       up.z,       0},
                 {forward.x, forward.y, forward.z,    0},
                 {0,          0,          0,          1}}};
    return Rot*Mov;
}

mat4 mat4::perspective(float fov, float ratio, float near, float far)
{
    float f_n = 1.0f/(far-near);
    fov *= M_PI/360;
    float f   = std::cos(fov)/std::sin(fov);
    ratio = 1.0f/ratio;

    mat4 M = {{{f*ratio,     0,        0,               0                },
                 {0,         f,        0,               0                },
                 {0,         0,        (far+near)*f_n,  -(2*far*near)*f_n },
                 {0,         0,        1,              1                }}};

//    mat4 M = {{{f*ratio,   0,        0,               0                },
//                 {0,         f,        0,               0                },
//                 {0,         0,        (far+near)*f_n,  (2*far*near)*f_n },
//                 {0,         0,        -1,              0                }}};
//    mat.mat[2][2] = - mat.mat[2][2];
    return M;
}

mat4 mat4::operator*(mat4 N)
{
    mat4 M = {{{0, 0, 0, 0},
               {0, 0, 0, 0},
               {0, 0, 0, 0},
               {0, 0, 0, 0}}};

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            for(int k = 0; k < 4; k++)
            {
                M.mat[i][j] += mat[i][k]*N.mat[k][j];
            }
        }
    }

//    x = (matrix.mat[0][0]*u.x) + (matrix.mat[0][1]*u.y) + (matrix.mat[0][2]*u.z) + (matrix.mat[0][3]*u.w);
//    y = (matrix.mat[1][0]*u.x) + (matrix.mat[1][1]*u.y) + (matrix.mat[1][2]*u.z) + (matrix.mat[1][3]*u.w);
//    z = (matrix.mat[2][0]*u.x) + (matrix.mat[2][1]*u.y) + (matrix.mat[2][2]*u.z) + (matrix.mat[2][3]*u.w);
//    w = (matrix.mat[3][0]*u.x) + (matrix.mat[3][1]*u.y) + (matrix.mat[3][2]*u.z) + (matrix.mat[3][3]*u.w);

    return M;
}



float4 float4::operator*=(mat4 matrix)
{
    float4 u(*this);

//    for(int i = 0; i < 4; i++)
//    {
//        this->operator [](i) = 0.0f;
//        for(int j = 0; j < 4; j++)
//        {
//            this->operator [](i) += u[j]*matrix.mat[i][j];
//        }
//    }

    x = (matrix.mat[0][0]*u.x) + (matrix.mat[0][1]*u.y) + (matrix.mat[0][2]*u.z) + (matrix.mat[0][3]*u.w);
    y = (matrix.mat[1][0]*u.x) + (matrix.mat[1][1]*u.y) + (matrix.mat[1][2]*u.z) + (matrix.mat[1][3]*u.w);
    z = (matrix.mat[2][0]*u.x) + (matrix.mat[2][1]*u.y) + (matrix.mat[2][2]*u.z) + (matrix.mat[2][3]*u.w);
    w = (matrix.mat[3][0]*u.x) + (matrix.mat[3][1]*u.y) + (matrix.mat[3][2]*u.z) + (matrix.mat[3][3]*u.w);

    return *this;
}

float const &float4::operator[](int i) const
{
    switch(i){
    case 0: return x;
    case 1: return y;
    case 2: return z;
    default: return w;
    }
}

float &float4::operator[](int i)
{
    switch(i){
    case 0: return x;
    case 1: return y;
    case 2: return z;
    default: return w;
    }
}

float4 float4::normalize()
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

float4 float4::crossProduct(float4 u, float4 v)
{
    return float4((u.y*v.z)-(u.z*v.y),
                  (u.z*v.x)-(u.x*v.z),
                  (u.x*v.y)-(u.y*v.x));
}

float float4::dotProduct(float4 u, float4 v)
{
    return (u.x*v.x)+(u.y*v.y)+(u.z*v.z);
}

float4 float4::operator-()
{
    x=-x;
    y=-y;
    z=-z;
    z=-w;
    return *this;
}

float4 float4::operator/=(float a)
{
    x/=a;
    y/=a;
    z/=a;
    w/=a;

    return *this;
}

float float4::len()
{
    return std::sqrt((x*x)+(y*y)+(z*z));
}
