#ifndef SCANLINE_H
#define SCANLINE_H
#include "buffer.h"

class scanline
{
public:
    scanline(int width, int height);

    buffer buf;

    void render();

};

#endif // SCANLINE_H
