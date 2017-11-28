#ifndef SCANLINE_H
#define SCANLINE_H
#include "buffer.h"
#include "vertexprocessor.h"
#include "fragmentprocessor.h"

class scanline
{
public:
    scanline(int width, int height);

    void render();

private:

    float4 OX = {1.0f, 0.0f, 0.0f};
    float4 OY = {0.0f, 1.0f, 0.0f};
    float4 OZ = {0.0f, 0.0f, 1.0f};

    buffer buf;
    vertexProcessor vp;
    fragmentProcessor fp;
};

#endif // SCANLINE_H
