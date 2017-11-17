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
    std::vector<mesh> objects;
    objects.push_back(mesh("boxy.obj"));
    objects.push_back(mesh(1.0f, 1.0f, 1.0f));
    objects[1].Tv = {-0.5f,-0.5f,0.85f};

    float4 up    (0.0f, 1.0f, 0.0f);
    float4 eye   (0.0f, 0.0f, -0.0f);
    float4 target(0.0f, 0.0f, 0.5f);

    mat4 V = mat4::lookAt(up,eye,target);
    mat4 P = mat4::perspective(45.0f, buf.width*1.0f/buf.height, 0.5, 3);

    for(int o = 0; o < objects.size(); o++)
    {
        mat4 T = mat4::translate(objects[o].Tv);

        mat4 Rx = mat4::rotate(objects[o].Rv.x,OX);
        mat4 Ry = mat4::rotate(objects[o].Rv.y,OY);
        mat4 Rz = mat4::rotate(objects[o].Rv.z,OZ);
        mat4 R = Rz*Ry*Rx;
        mat4 S = mat4::scale(objects[o].Sv);

        mat4 M = T*S*R;
        mat4 MVP = P*V*M;

        for(int i = 0; i < objects[o].vertices.size(); i++)
        {
            objects[o].vertices[i]->operator*=(MVP);

            objects[o].vertices[i]->operator/=(objects[o].vertices[i]->pos.w);

            std::cout << objects[o].vertices[i]->pos.x << " "
                      << objects[o].vertices[i]->pos.y << " "
                      << objects[o].vertices[i]->pos.z << " "
                      << objects[o].vertices[i]->pos.w << std::endl;
        }

        if(buf.width>0 && buf.height > 0){

            float stepx = 1.0/buf.width;
            float stepy = 1.0/buf.height;

            for(int i = 0; i < objects[o].triangles.size(); i++)
            {

                triangle tri = *(objects[o].triangles[i]);

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

                maxx>1? maxx = 1: maxx<-1? maxx = -1: true;
                maxy>1? maxy = 1: maxy<-1? maxy = -1: true;

                minx>1? minx = 1: minx<-1? minx = -1: true;
                miny>1? miny = 1: miny<-1? miny = -1: true;

                maxx =  1.0f; maxy =  1.0f;
                minx = -1.0f; miny = -1.0f;

                //            minx *= buf.width;
                //            maxx *= buf.width;

                //            miny *= buf.height;
                //            maxy *= buf.height;

                // check for intersection

                for(float x = minx; x < maxx; x += stepx)
                {
                    for(float y = miny; y < maxy; y += stepy)
                    {
                        hit test = tri.intersection( x, y );
                        if(test.isHit)
                        {
                            float depth = (tri.A->pos.z * test.areas.x) + (tri.B->pos.z * test.areas.y) + (tri.C->pos.z * test.areas.z);

                            color diffuse = (tri.A->col * test.areas.x) +
                                    (tri.B->col * test.areas.y) +
                                    (tri.C->col * test.areas.z);
                            if(depth >= -1 && depth <= 1)
                            {
                                int x1 = (x+1) * buf.width * 0.5f, y1 = (y+1) * buf.height * 0.5f;
                                bool test2 = (depth < buf.depth[(int)(buf.width * y1 + x1)]);
                                bool test3 = buf.depth[(int)(buf.width * y1 + x1)] == 1;
                                if(test2 || test3 || !depthTestEnabled)
                                {
                                    buf.write(x1,y1 , diffuse, depth);
                                }
                            }
                        }
                    }
                }
            }
        }

        //save to TGA
    }
    serializer::bufferToTGA(buf);
}
