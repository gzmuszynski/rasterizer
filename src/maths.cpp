#define _USE_MATH_DEFINES
#include "maths.h"

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

mat4 mat4::transpose()
{
    mat4 M = {{{mat[0][0], mat[1][0], mat[2][0], mat[3][0]},
               {mat[0][1], mat[1][1], mat[2][1], mat[3][1]},
               {mat[0][2], mat[1][2], mat[2][2], mat[3][2]},
               {mat[0][3], mat[1][3], mat[2][3], mat[3][3]}}};
    return M;
}

mat4 mat4::inverse()
{
    mat4 inv;

    inv.mat[0][0] = mat[1][1] * mat[2][2] * mat[3][3] - mat[1][1] * mat[2][3] * mat[3][2] - mat[2][1] * mat[1][2] * mat[3][3] +
                    mat[2][1] * mat[1][3] * mat[3][2] + mat[3][1] * mat[1][2] * mat[2][3] - mat[3][1] * mat[1][3] * mat[2][2];

    inv.mat[1][0] =-mat[1][0] * mat[2][2] * mat[3][3] + mat[1][0] * mat[2][3] * mat[3][2] + mat[2][0] * mat[1][2] * mat[3][3] -
                    mat[2][0] * mat[1][3] * mat[3][2] - mat[3][0] * mat[1][2] * mat[2][3] + mat[3][0] * mat[1][3] * mat[2][2];

    inv.mat[2][0] = mat[1][0] * mat[2][1] * mat[3][3] - mat[1][0] * mat[2][3] * mat[3][1] - mat[2][0] * mat[1][1] * mat[3][3] +
                    mat[2][0] * mat[1][3] * mat[3][1] + mat[3][0] * mat[1][1] * mat[2][3] - mat[3][0] * mat[1][3] * mat[2][1];

    inv.mat[3][0] =-mat[1][0] * mat[2][1] * mat[3][2] + mat[1][0] * mat[2][2] * mat[3][1] +mat[2][0]  * mat[1][1] * mat[3][2] -
                    mat[2][0] * mat[1][2] * mat[3][1] - mat[3][0] * mat[1][1] * mat[2][2] + mat[3][0] * mat[1][2] * mat[2][1];

    inv.mat[0][1] =-mat[0][1] * mat[2][2] * mat[3][3] + mat[0][1] * mat[2][3] * mat[3][2] + mat[2][1] * mat[0][2] * mat[3][3] -
                    mat[2][1] * mat[0][3] * mat[3][2] - mat[3][1] * mat[0][2] * mat[2][3] + mat[3][1] * mat[0][3] * mat[2][2];

    inv.mat[1][1] = mat[0][0] * mat[2][2] * mat[3][3] - mat[0][0] * mat[2][3] * mat[3][2] - mat[2][0] * mat[0][2] * mat[3][3] +
                    mat[2][0] * mat[0][3] * mat[3][2] + mat[3][0] * mat[0][2] * mat[2][3] - mat[3][0] * mat[0][3] * mat[2][2];

    inv.mat[2][1] =-mat[0][0] * mat[2][1] * mat[3][3] + mat[0][0] * mat[2][3] * mat[3][1] + mat[2][0] * mat[0][1] * mat[3][3] -
                    mat[2][0] * mat[0][3] * mat[3][1] - mat[3][0] * mat[0][1] * mat[2][3] + mat[3][0] * mat[0][3] * mat[2][1];

    inv.mat[3][1] = mat[0][0] * mat[2][1] * mat[3][2] - mat[0][0] * mat[2][2] * mat[3][1] - mat[2][0] * mat[0][1] * mat[3][2] +
                    mat[2][0] * mat[0][2] * mat[3][1] + mat[3][0] * mat[0][1] * mat[2][2] - mat[3][0] * mat[0][2] * mat[2][1];

    inv.mat[0][2] = mat[0][1] * mat[1][2] * mat[3][3] - mat[0][1] * mat[1][3] * mat[3][2] - mat[1][1] * mat[0][2] * mat[3][3] +
                    mat[1][1] * mat[0][3] * mat[3][2] + mat[3][1] * mat[0][2] * mat[1][3] - mat[3][1] * mat[0][3] * mat[1][2];

    inv.mat[1][2] =-mat[0][0] * mat[1][2] * mat[3][3] + mat[0][0] * mat[1][3] * mat[3][2] + mat[1][0] * mat[0][2] * mat[3][3] -
                    mat[1][0] * mat[0][3] * mat[3][2] - mat[3][0] * mat[0][2] * mat[1][3] + mat[3][0] * mat[0][3] * mat[1][2];

    inv.mat[2][2] = mat[0][0] * mat[1][1] * mat[3][3] - mat[0][0] * mat[1][3] * mat[3][1] - mat[1][0] * mat[0][1] * mat[3][3] +
                    mat[1][0] * mat[0][3] * mat[3][1] + mat[3][0] * mat[0][1] * mat[1][3] - mat[3][0] * mat[0][3] * mat[1][1];

    inv.mat[3][2] =-mat[0][0] * mat[1][1] * mat[3][2] + mat[0][0] * mat[1][2] * mat[3][1] + mat[1][0] * mat[0][1] * mat[3][2] -
                    mat[1][0] * mat[0][2] * mat[3][1] - mat[3][0] * mat[0][1] * mat[1][2] + mat[3][0] * mat[0][2] * mat[1][1];

    inv.mat[0][3] =-mat[0][1] * mat[1][2] * mat[2][3] + mat[0][1] * mat[1][3] * mat[2][2] + mat[1][1] * mat[0][2] * mat[2][3] -
                    mat[1][1] * mat[0][3] * mat[2][2] - mat[2][1] * mat[0][2] * mat[1][3] + mat[2][1] * mat[0][3] * mat[1][2];

    inv.mat[1][3] = mat[0][0] * mat[1][2] * mat[2][3] - mat[0][0] * mat[1][3] * mat[2][2] - mat[1][0] * mat[0][2] * mat[2][3] +
                    mat[1][0] * mat[0][3] * mat[2][2] + mat[2][0] * mat[0][2] * mat[1][3] - mat[2][0] * mat[0][3] * mat[1][2];

    inv.mat[2][3] =-mat[0][0] * mat[1][1] * mat[2][3] + mat[0][0] * mat[1][3] * mat[2][1] + mat[1][0] * mat[0][1] * mat[2][3] -
                    mat[1][0] * mat[0][3] * mat[2][1] - mat[2][0] * mat[0][1] * mat[1][3] + mat[2][0] * mat[0][3] * mat[1][1];

    inv.mat[3][3] = mat[0][0] * mat[1][1] * mat[2][2] - mat[0][0] * mat[1][2] * mat[2][1] - mat[1][0] * mat[0][1] * mat[2][2] +
                    mat[1][0] * mat[0][2] * mat[2][1] + mat[2][0] * mat[0][1] * mat[1][2] - mat[2][0] * mat[0][2] * mat[1][1];

    float det = mat[0][0] * inv.mat[0][0] + mat[0][1] * inv.mat[1][0] + mat[0][2] * inv.mat[2][0] + mat[0][3] * inv.mat[3][0];

    if (det == 0)
        return *this;

    det = 1.0 / det;

    for(int x = 0; x < 4; x++)
    {
        for(int y = 0; y < 4; y++)
        {
            inv.mat[x][y] *= det;
        }
    }

    return inv;
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

float4 float4::operator*(float a)
{
    float4 n(*this);
    n.y*=a;
    n.z*=a;
    n.x*=a;
    n.w*=a;

    return n;
}

float4 float4::operator+(float4 v)
{
    float4 n(*this);
    n.y+=v.y;
    n.z+=v.z;
    n.x+=v.x;
    n.w+=v.w;

    return n;
}

float4 float4::operator*(float4 v)
{
    float4 n(*this);
    n.y*=v.y;
    n.z*=v.z;
    n.x*=v.x;
    n.w*=v.w;

    return n;
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
    float length = len2();
    if(length!=0)
    {
        length = invSqrt(length);
        y*=length;
        z*=length;
        x*=length;
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
    if(a==0)
        a = 1.0f/0.0001f;
    else
        a = 1.0f/a;
    y*=a;
    z*=a;
    x*=a;
    w*=a;

    return *this;
}

float float4::len()
{
    return std::sqrt((x*x)+(y*y)+(z*z));
}

float float4::len2()
{
    return (x*x)+(y*y)+(z*z);
}

float float4::invSqrt(float n)
{

    long i;
    float x2, y;
    const float threehalfs = 1.5F;

    x2 = n * 0.5F;
    y  = n;
    i  = * ( long * ) &y;                       // evil floating point bit level hacking
    i  = 0x5f3759df - ( i >> 1 );               // what the fuck?
    y  = * ( float * ) &i;
    y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
    //      y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

    return y;
}
