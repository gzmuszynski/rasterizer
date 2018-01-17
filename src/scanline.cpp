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
    color col = {0xFFFFFFFF};
    objects.push_back(mesh("boxy.obj",col)); //draw object
    objects[0].Tv = float4(0.0f,0.0f,0.0f); //translate vector
    objects[0].Rv = float4(0.0f,0.0f,0.0f); //rotate vector
    objects[0].Sv = float4(1.0f,1.0f,1.0f); //scale vector

    float4 up    (0.0f, 1.0f, 0.0f);
    float4 eye   (0.0f, -0.0f, -0.8f);
    float4 target(0.0f, 0.0f, 1.0f);

    light* l1 = new light(float4(0.0,0.5,0.5,1));
    l1->ambient  = 0xFF222222;
    l1->specular = 0xFFFFFFFF;
    l1->diffuse  = 0xFFFFFFFF;
    light* l2 = new light(float4(0.0,0.5,-1.5,1));
    l2->ambient  = 0xFF111111;
    l2->specular = 0xFFFFFFFF;
    l2->diffuse  = 0xFFFFFFFF;

    std::vector<light*> lights;
    lights.push_back(l1);
//    lights.push_back(l2);

    //VERTEX PROCESSOR BEGIN

    clock_t begin = std::clock();



    for(int o = 0; o < objects.size(); o++)
    {
        vp.setIdentity();

        vp.lookAt(up,eye,target);
        vp.perspective(80.0f, buf.width*1.0f/buf.height, 0.5, 2);

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
