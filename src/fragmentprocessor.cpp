#include "fragmentprocessor.h"
#include <stdio.h>
#include <iostream>

void fragmentProcessor::fillTriangle(buffer &buf)
{
    double stepx = 2.0/buf.width;
    double stepy = 2.0/buf.height;

    double maxx, minx, maxy, miny;  // min-max for basic rendertime saving
    minmax(minx, miny, maxx, maxy);
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
            hit test = tri->intersection( x, y );
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
    double f1 = test.areas[0];
    double f2 = test.areas[1];
    double f3 = test.areas[2];

    color final = (tri->A->col*f1)+(tri->B->col*f2)+(tri->C->col*f3);

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
