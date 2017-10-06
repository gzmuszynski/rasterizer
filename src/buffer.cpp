#include "buffer.h"

void buffer::clear()
{
    for(int x = 0; x < width; x++){
        for(int y = 0; y < height; y++){
            color[(width*y)+x] = 0x00000000;
            depth[(width*y)+x] = 0;
        }
    }
}

void buffer::clearColor()
{
    for(int x = 0; x < width; x++){
        for(int y = 0; y < height; y++){
            color[(width*y)+x] = 0x00000000;
        }
    }

}

void buffer::clearDepth()
{
    for(int x = 0; x < width; x++){
        for(int y = 0; y < height; y++){
            depth[(width*y)+x] = 0;
        }
    }
}

void buffer::initBuffer(int width, int height){
    this->width = width;
    this->height = height;

    color = new unsigned int[width*height];
    depth = new float[width*height];
    clear();
}

void buffer::write(int x, int y, unsigned int color, float depth){
    this->color[(width*y)+x] = color;
    this->depth[(width*y)+x] = depth;
}
