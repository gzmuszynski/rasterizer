#include "mesh.h"
#include "scanline.h"
#include "serializer.h"
#include <iostream>
#include <stdio.h>
#include <vector>
#include <math.h>

scanline::scanline(int width, int height)
{
    buf.initBuffer(width, height);
}

void scanline::render()
{
    // define CW triangle


    mesh object("boxy.obj");

    float3 Tv = {0.5f, 0.5f,  0.0f};
    float  a  = 180.0f;
    float3 Rv = {0.0f, 0.0f,  1.0f};
    float3 Sv = {1.0f, 1.0f,  1.0f};

    mat4 T = mat4::translate(Tv);
    mat4 R = mat4::rotate(a,Rv);
    mat4 S = mat4::scale(Sv);

    mat4 MW = R*S*T;

    for(int i = 0; i < object.vertices.size(); i++)
    {
        object.vertices[i]->operator*=(MW);
        std::cout << object.vertices[i]->pos.x << " " << object.vertices[i]->pos.y << " " <<object.vertices[i]->pos.z << " " << std::hex << object.vertices[i]->col.argb << std::endl;
    }

    if(buf.width>0 && buf.height > 0){

        float stepx = 1.0/buf.width;
        float stepy = 1.0/buf.height;

        for(int i = 0; i < object.triangles.size(); i++)
        {

            triangle tri = *(object.triangles[i]);
            // min-max for basic rendertime saving

            float maxx, minx, maxy, miny;

            maxy = (tri.A->pos.y > tri.B->pos.y )? tri.A->pos.y : tri.B->pos.y;
            maxx = (tri.A->pos.x > tri.B->pos.x )? tri.A->pos.x : tri.B->pos.x;
            minx = (tri.A->pos.x < tri.B->pos.x )? tri.A->pos.x : tri.B->pos.x;
            miny = (tri.A->pos.y < tri.B->pos.y )? tri.A->pos.y : tri.B->pos.y;

            maxx = (maxx     > tri.C->pos.x )? maxx     : tri.C->pos.x;
            minx = (minx     < tri.C->pos.x )? minx     : tri.C->pos.x;
            maxy = (maxy     > tri.C->pos.y )? maxy     : tri.C->pos.y;
            miny = (miny     < tri.C->pos.y )? miny     : tri.C->pos.y;

            maxx>1? maxx = 1: maxx<0? maxx = 0: true;
            maxy>1? maxy = 1: maxy<0? maxy = 0: true;

            minx>1? minx = 1: minx<0? minx = 0: true;
            miny>1? miny = 1: miny<0? miny = 0: true;

            maxx = 1.0f; maxy = 1.0f;
            minx = 0.0f; miny = 0.0f;

            minx *= buf.width;
            maxx *= buf.width;

            miny *= buf.height;
            maxy *= buf.height;

            // check for intersection

            for(int x = minx; x <= maxx; x++)
            {
                for(int y = miny; y <= maxy; y++)
                {
                    hit test = tri.intersection(x * stepx, y * stepy);
                    if(test.isHit)
                    {
                        float depth = (tri.A->pos.z * test.areas.x) + (tri.B->pos.z * test.areas.y) + (tri.C->pos.z * test.areas.z);

                        color diffuse = (tri.A->col * test.areas.x) +
                                (tri.B->col * test.areas.y) +
                                (tri.C->col * test.areas.z);
                        if(i == 0 || depth < buf.depth[(int)(buf.width * y + x)] || buf.depth[(int)(buf.width * y + x)] == 0 || !depthTestEnabled)
                        {
                            buf.write(x,y, diffuse, depth);
                        }
                    }
                }
            }
        }

        //save to TGA

        serializer::bufferToTGA(buf);
    }
}
