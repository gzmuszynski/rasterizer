#include "scanline.h"
#include "serializer.h"
#include <iostream>
#include <stdio.h>
#include <vector>

scanline::scanline(int width, int height)
{
    buf.initBuffer(width, height);
}

void scanline::render()
{
    if(buf.width>0 && buf.height > 0){

        float stepx = 1.0/buf.width;
        float stepy = 1.0/buf.height;

        // define CW triangle

        std::vector<triangle> triangles;
        triangle tri1 = { { 0.0f, 0.0f, 1.0f },
                          { 0.5f, 1.0f, 0.5f },
                          { 1.0f, 0.5f, 0.0f },
                          0xFFFF0000,
                          0xFF00FF00,
                          0xFF0000FF }; // ARGB

        triangle tri2 { { 0.4f, 0.4f, 0.0f },
                        { 0.5f, 0.6f, 0.5f },
                        { 0.6f, 0.4f, 1.0f },
                        0xFF996699 ,
                        0xFF996699 ,
                        0xFF996699 }; // ARGB

        triangles.push_back(tri1);
        triangles.push_back(tri2);

        for(int i = 0; i < triangles.size(); i++)
        {

            triangle tri = triangles[i];
            // min-max for basic rendertime saving

            float maxx, minx, maxy, miny;

            maxx = (tri.A.x > tri.B.x )? tri.A.x : tri.B.x;
            maxx = (maxx     > tri.C.x )? maxx     : tri.C.x;

            minx = (tri.A.x < tri.B.x )? tri.A.x : tri.B.x;
            minx = (minx     < tri.C.x )? minx     : tri.C.x;

            maxy = (tri.A.y > tri.B.y )? tri.A.y : tri.B.y;
            maxy = (maxy     > tri.C.y )? maxy     : tri.C.y;

            miny = (tri.A.y < tri.B.y )? tri.A.y : tri.B.y;
            miny = (miny     < tri.C.y )? miny     : tri.C.y;

            // check for intersection

            for(float x = minx * buf.width; x < maxx * buf.width; x++)
            {
                for(float y = miny * buf.height; y < maxy * buf.height; y++)
                {
                    hit test = tri.intersection(x * stepx, y * stepy);
                    if(test.isHit)
                    {
                        float depth = (tri.A.z * test.areas.x) + (tri.B.z * test.areas.y) + (tri.C.z * test.areas.z);

                        color diffuse = (tri.colA * test.areas.x) +
                                (tri.colB * test.areas.y) +
                                (tri.colC * test.areas.z);
                        if(i == 0 || depth < buf.depth[(int)(buf.width * y + x)] || !depthTestEnabled)
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
