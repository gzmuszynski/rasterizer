#include "buffer.h"

void buffer::clear()
{
    for(int x = 0; x < width; x++){
        for(int y = 0; y < height; y++){
            diffuse[(width*y)+x] = 0x00000000;
            depth[(width*y)+x] = 1.0f;
        }
    }
}

void buffer::clearColor()
{
    for(int x = 0; x < width; x++){
        for(int y = 0; y < height; y++){
            diffuse[(width*y)+x] = 0x00000000;
        }
    }

}

void buffer::clearDepth()
{
    for(int x = 0; x < width; x++){
        for(int y = 0; y < height; y++){
            depth[(width*y)+x] = 1.0f;
        }
    }
}

void buffer::initBuffer(int width, int height){
    this->width = width;
    this->height = height;

    diffuse = new color[width*height];
    depth = new float[width*height];
    clear();
}

void buffer::write(int x, int y, color diffuse, float depth){
    this->diffuse[(width*y)+x] = diffuse;
    this->depth[(width*y)+x] = depth;
}
