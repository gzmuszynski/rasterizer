#include "texture.h"
#include <fstream>

texture::texture(std::string filename)
{
    std::ifstream bitmap(filename, std::ios::binary);
    if(bitmap.is_open())
    {
        unsigned char header[18];

        bitmap.read((char*)&header,18);

        width = header[12] + (header[13] << 8);
        height = header[14] + (header[15] << 8);

        this->bitmap = new color[width*height];

        for(int y = 0; y < height; y++)
        {
            for(int x = 0; x < width; x++)
            {
                unsigned int texel;
                bitmap.read((char*)&texel, sizeof(unsigned int));

                this->bitmap[x + (y*width)] = color{texel};
            }
        }
        bitmap.close();
    }
    wrap = REPEAT;
    filter = NEAREST;
}

color texture::sample(float s, float t)
{
    color texSample = color{0xFFFFFFFF};

    float u,v;

    if(wrap == CLAMP)
    {
        u = std::max(0.0f,std::min((s*width), width-1.0f));
        v = std::max(0.0f,std::min((t*height),height-1.0f));
    }
    if(wrap == REPEAT)
    {
        u = (s - std::floor(s)) * width;
        v = (t - std::floor(t)) * width;
    }

    if(filter == NEAREST)
    {
        texSample = bitmap[(int)u + (int)v*width];
    }
    if(filter == LINEAR)
    {

    }
    return texSample;
}
