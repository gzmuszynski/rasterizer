#ifndef BUFFER_H
#define BUFFER_H

#include "color.h"

struct buffer
{
    int width, height;

    color* diffuse;
    float* depth;

    void clear();
    void clearColor();
    void clearDepth();

    void initBuffer(int width, int height);

    void write(int x, int y, color diffuse, float depth);
};

#endif // BUFFER_H
