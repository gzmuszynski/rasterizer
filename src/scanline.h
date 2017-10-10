#ifndef SCANLINE_H
#define SCANLINE_H
#include "buffer.h"
#include "triangle.h"

class scanline
{
public:
    scanline(int width, int height);

    void render();

private:
    bool depthTestEnabled = true;

    buffer buf;
};

#endif // SCANLINE_H
