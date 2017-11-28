#include "scanline.h"
#include "serializer.h"

#include <iostream>
#include <stdio.h>
#include <vector>
#include <ctime>

scanline::scanline(int width, int height)
{
    buf.initBuffer(width, height);
    vp.setIdentity();
}

void scanline::render()
{
    std::vector<mesh> objects;

    objects.push_back(mesh("boxy.obj"));
    objects.push_back(mesh(1.0f, 1.0f, 1.0f));
    objects[1].Tv = {-0.5f,-0.5f,0.85f};

    float4 up    (0.0f, 1.0f, 0.0f);
    float4 eye   (0.0f, -0.0f, -0.5f);
    float4 target(0.0f, 0.0f, 0.0f);

    light* l1 = new light(float4(0,0.45,0.45,1),float4(0,1,0));
    l1->ambient  = 0x00000000;
    l1->diffuse  = 0xFFFFFFFF;
    l1->specular = 0x00000000;

    std::vector<light*> lights;
    lights.push_back(l1);

    //VERTEX PROCESSOR BEGIN

    clock_t begin = std::clock();

    vp.lookAt(up,eye,target);
    vp.perspective(90.0f, buf.width*1.0f/buf.height, 0.2, 1.5);

    for(int o = 0; o < objects.size(); o++)
    {


        vp.vertexBuffer = objects[o].vertices;
        vp.lightBuffer  = lights;

        vp.translate(objects[o].Tv);

        vp.rotate(objects[o].Rv.x,OX);
        vp.rotate(objects[o].Rv.y,OY);
        vp.rotate(objects[o].Rv.z,OZ);

        vp.scale(objects[o].Sv);

        vp.transform();

        //VERTEX PROCESSOR END

        //FRAGMENT PROCESSOR BEGIN

        fp.lights = lights;

        if(buf.width>0 && buf.height > 0){

            for(int i = 0; i < objects[o].triangles.size(); i++)
            {

                fp.tri = (objects[o].triangles[i]);
                fp.fillTriangle(buf);

            }
        }

        //FRAGMENT PROCESSOR END


    }

    clock_t end = std::clock();

    clock_t time = end - begin;

    std::cout << "time: " << time << "ms, FPS: " << 1000.0f/time << std::endl;;
    //save to TGA
    serializer::bufferToTGA(buf);
}
