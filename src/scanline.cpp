#include "scanline.h"
#include "triangle.h"
#include "buffer.h"
#include "serializer.h"
#include <iostream>
#include <stdio.h>

scanline::scanline(int width, int height)
{
    buf.initBuffer(width, height);
}

void scanline::render()
{
    if(buf.width>0 && buf.height > 0){

        float stepx = 1.0/buf.width;
        float stepy = 1.0/buf.height;

        // define CCW triangle

        triangle tri ( { 0.0, 0.0, 0.0 },
                       { 1.0, 0.0, 0.0 },
                       { 0.5, 1.0, 0.0 },
                       0xFF336699 ); // ARGB


        // min-max for basic rendertime saving

        float maxx, minx, maxy, miny;

        maxx = (tri.p1.x > tri.p2.x )? tri.p1.x : tri.p2.x;
        maxx = (maxx     > tri.p3.x )? maxx     : tri.p3.x;

        minx = (tri.p1.x < tri.p2.x )? tri.p1.x : tri.p2.x;
        minx = (minx     < tri.p3.x )? minx     : tri.p3.x;

        maxy = (tri.p1.y > tri.p2.y )? tri.p1.y : tri.p2.y;
        maxy = (maxy     > tri.p3.y )? maxy     : tri.p3.y;

        miny = (tri.p1.y < tri.p2.y )? tri.p1.y : tri.p2.y;
        miny = (miny     < tri.p3.y )? miny     : tri.p3.y;

        // check for intersection

        for(float x = minx * buf.width; x < maxx * buf.width; x++)
        {
            for(float y = miny * buf.height; y < maxy * buf.height; y++)
            {
                bool hit = tri.intersection(x * stepx, y * stepy);
                if(hit)
                {
                    buf.write(x,y, tri.color, 1);
                }
            }
        }

        //save to TGA

        serializer::bufferToTGA(buf);
    }
}
