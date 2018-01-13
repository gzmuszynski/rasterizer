#include "fragmentprocessor.h"
#include <stdio.h>
#include <iostream>
//#define NOMINMAX

void fragmentProcessor::fillTriangle(buffer &buf)
{
    double stepx = 2.0/buf.width;
    double stepy = 2.0/buf.height;

    double maxx, minx, maxy, miny;  // min-max for basic rendertime saving
//#ifdef NOMINMAX
//    minx = -1;
//    miny = -1;
//    maxx = 1;
//    maxy = 1;
//#endif
//#ifndef NOMINMAX
    minmax(minx, miny, maxx, maxy);
//#endif
    // check for intersection

    int minix = (minx+1)*buf.width*0.5;
    int maxix = (maxx+1)*buf.width*0.5;
    int miniy = (miny+1)*buf.height*0.5;
    int maxiy = (maxy+1)*buf.height*0.5;

    for(int x1 = minix; x1 < maxix; x1++)
    {
        double x = (x1*stepx)-1;

        for(int y1 = miniy; y1 < maxiy; y1++)
        {
            double y = (y1*stepy)-1;
#ifdef FISHEYE
            hit test = tri->intersectionCos( x, y );
#endif
#ifndef FISHEYE
            hit test = tri->intersection( x, y );
#endif
            if(test.isHit)
            {
                float depth = (tri->A->pos.z * test.areas.x) + (tri->B->pos.z * test.areas.y) + (tri->C->pos.z * test.areas.z);

                if(depth >= 0 && depth <= 1)
                {
//                    int x1 = (x+1) * buf.width * 0.5f, y1 = (y+1) * buf.height * 0.5f;
                    bool test2 = (depth < buf.depth[(int)(buf.width * y1 + x1)]);
                    bool test3 = buf.depth[(int)(buf.width * y1 + x1)] == 1;
                    if(test2 || test3 || !depthTestEnabled)
                    {
                        color pixel = shader(test);

                        buf.write(x1,y1 , pixel, depth);
                    }
                }
            }
        }
    }
}

void fragmentProcessor::forwardMVP(mat4 M, mat4 V, mat4 P)
{
    this->M = M;
    this->V = V;
    this->P = P;
}

color fragmentProcessor::shader(hit test)
{
    material* mat = tri->mat;

    double f1 = test.areas[0] * tri->A->pos.w;
    double f2 = test.areas[1] * tri->B->pos.w;
    double f3 = test.areas[2] * tri->C->pos.w;

    double div = 1.0f/ (f1 + f2 + f3);

    f1 *= div;
    f2 *= div;
    f3 *= div;


    color final = {0xFF000000};
    color ambient = {0}, diffuse = {0}, specular = {0};

    float4 point (tri->A->pos2 * test.areas[0] + tri->B->pos2 * test.areas[1] + tri->C->pos2 * test.areas[2]);
    float4 normal(tri->A->norm * f1 + tri->B->norm * f2 + tri->C->norm * f3);
    normal = normal.normalize();

    float s = tri->A->uv.x * f1 + tri->B->uv.x * f2 + tri->C->uv.x * f3;
    float t = tri->A->uv.y * f1 + tri->B->uv.y * f2 + tri->C->uv.y * f3;

    for(int i = 0; i < lights.size(); i++)
    {
        light *l1 = lights[i];
        ambient + l1->ambient * mat->ambient * mat->ambientTexture->sample(s,t);

        float4 lightVec = l1->getVector(point);
        float attenuation = l1->getAttenuation(lightVec);

        lightVec = lightVec.normalize();

        float LdotN = std::min(float4::dotProduct( lightVec, normal),1.0f);
        diffuse + (l1->diffuse * attenuation * std::max(0.0f,LdotN) * mat->diffuse * mat->diffuseTexture->sample(s,t)); // lambertian

        float4 viewVec = -(point.normalize());
        float4 halfVec = (viewVec+-lightVec).normalize();

        float NdotH = std::max(0.0f,-float4::dotProduct(halfVec,normal));
        float shininessR = (mat->shininess.red()   * mat->shininessTexture->sample(s,t).red()  *(1.0f/255));
        float shininessG = (mat->shininess.green() * mat->shininessTexture->sample(s,t).green()*(1.0f/255));
        float shininessB = (mat->shininess.blue()  * mat->shininessTexture->sample(s,t).blue() *(1.0f/255));

        specular + (l1->specular * ((color{0xFFFF0000} * std::pow(NdotH, shininessR)) +
                                    (color{0xFF00FF00} * std::pow(NdotH, shininessG)) +
                                    (color{0xFF0000FF} * std::pow(NdotH, shininessB)))
                    * mat->specular * mat->specularTexture->sample(s,t));
        final = final + ambient + diffuse + specular;
//        final = ((color{0xFFFF0000} * s) +  (color{0xFF00FF00} * t)); // uv viewing debug
//        final = (color{0xFFFFFFFF} * ((lightVec*float4(0.5,0.5,0.5,1))+float4(0.5,0.5,0.5,0))); // light viewing debug
    }
//                final = (color{0xFFFFFFFF} * ((normal*float4(0.5,0.5,0.5,1))+float4(0.5,0.5,0.5,0))); // normal viewing debug
//                final = (color{0xFFFFFFFF} * ((point*float4(0.5,0.5,1.0,1))+float4(0.5,0.5,0.0,0))); // point viewing debug


    return final;
}

void fragmentProcessor::minmax(double &minx, double &miny, double &maxx, double &maxy)
{
    maxy = (tri->A->pos.y > tri->B->pos.y ) ? tri->A->pos.y : tri->B->pos.y;
    maxx = (tri->A->pos.x > tri->B->pos.x ) ? tri->A->pos.x : tri->B->pos.x;
    minx = (tri->A->pos.x < tri->B->pos.x ) ? tri->A->pos.x : tri->B->pos.x;
    miny = (tri->A->pos.y < tri->B->pos.y ) ? tri->A->pos.y : tri->B->pos.y;

    maxx = (maxx > tri->C->pos.x ) ? maxx : tri->C->pos.x;
    minx = (minx < tri->C->pos.x ) ? minx : tri->C->pos.x;
    maxy = (maxy > tri->C->pos.y ) ? maxy : tri->C->pos.y;
    miny = (miny < tri->C->pos.y ) ? miny : tri->C->pos.y;

    maxx>1? maxx = 1: maxx<-1? maxx = -1: true;
    maxy>1? maxy = 1: maxy<-1? maxy = -1: true;

    minx>1? minx = 1: minx<-1? minx = -1: true;
    miny>1? miny = 1: miny<-1? miny = -1: true;

    //    maxx =  1.0f; maxy =  1.0f;
    //    minx = -1.0f; miny = -1.0f;
}
