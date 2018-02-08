#define _USE_MATH_DEFINES
#include "vertexprocessor.h"
#include <stdio.h>
#include <iostream>

void vertexProcessor::setIdentity()
{
    M = mat4::identity();
    V = mat4::identity();
    P = mat4::identity();
}

void vertexProcessor::translate(float4 v)
{
    mat4 T = {{{1, 0, 0, v.x},
               {0, 1, 0, v.y},
               {0, 0, 1, v.z},
               {0, 0, 0, 1}}};
    M = T*M;
}

void vertexProcessor::scale(float4 v)
{
    mat4 S = {{{v.x, 0,   0,   0},
               {0,   v.y, 0,   0},
               {0,   0,   v.z, 0},
               {0,   0,   0,   1}}};
    M = S*M;
}

void vertexProcessor::rotate(float a, float4 v)
{
    float rad = M_PI/180.0f;

    float s = std::sin(a*rad), c = std::cos(a*rad);

    v = v.normalize();

    mat4 R = {{{v.x*v.x*(1-c)+c    , v.x*v.y*(1-c)-v.z*s, v.x*v.z*(1-c)+v.y*s, 0},
               {v.x*v.y*(1-c)+v.z*s,  v.y*v.y*(1-c)+c   , v.z*v.y*(1-c)-v.x*s, 0},
               {v.x*v.z*(1-c)-v.y*s, v.z*v.y*(1-c)+v.x*s, v.z*v.z*(1-c)+c    , 0},
               {0                  , 0                  , 0                  , 1}}};

    M = R*M;
}

void vertexProcessor::lookAt(float4 up, float4 eye, float4 target)
{
    view = eye;
    up = up.normalize();
    float4 forward = float4(eye,target).normalize();
    float4 right   = float4::crossProduct(up,forward).normalize();
    up      = float4::crossProduct(forward,right);

    mat4 Mov = {{{1, 0, 0, -eye.x},
                 {0, 1, 0, -eye.y},
                 {0, 0, 1, -eye.z},
                 {0, 0, 0, 1}}};

    mat4 Rot = {{{right.x,    right.y,    right.z,    0},
                 {up.x,       up.y,       up.z,       0},
                 {-forward.x, -forward.y, -forward.z, 0},
                 {0,          0,          0,          1}}};

    V = Rot*Mov;
}

void vertexProcessor::perspective(float fov, float ratio, float near, float far)
{
    if(far==near)
        return;
    float f_n = 1.0f/(near-far);
    fov *= M_PI/360;
    float s = std::sin(fov);
    float f = s != 0 ? std::cos(fov) / s : std::cos(fov) / 0.0001f;
    ratio = 1.0f/ratio;

    mat4 Per = {{{f*ratio,   0,        0,               0                },
                 {0,         f,        0,               0                },
                 {0,         0,        (far+near)*f_n,  (2*far*near)*f_n },
                 {0,         0,        -1,              0                }}};
    P = Per;
}

void vertexProcessor::transform()
{
    MV = V*M;
    MVP = P*MV;
    MVT = MV.inverse().transpose();

    for(int i = 0; i < vertexBuffer.size(); i++)
    {
        shader(vertexBuffer[i]);
    }
}

void vertexProcessor::shader(vertex *v)
{
    float4 pos = v->pos;
    float4 N = v->norm;

    pos *= M;
    N *= M.inverse().transpose();

    color final;

    for(light* l:lightBuffer)
    {
        float4 L = l->getVector(pos).normalize();

        color ambient = v->col*l->ambient;
        color diffuse = v->col*l->diffuse*std::max(0.0f,float4::dotProduct(L,N));


        float4 H = (view+L).normalize();
        float NdotH = float4::dotProduct(N,H);

        color specular = v->col*l->specular*std::pow(std::max(0.0f,NdotH),40);
        final = ambient+diffuse+specular;
    }
    v->col = final;

    v->pos*=MVP;
    v->pos/=v->pos.w;
}
