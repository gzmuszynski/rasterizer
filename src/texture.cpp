#include "texture.h"
#include <fstream>

texture::texture()
{
    width  = 0;
    height = 0;
}

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
}

color texture::sample(float s, float t)
{
    color texSample = color{0xFFFFFFFF};

    float u,v;

    if(height == 0 || width == 0)
        return color{0xFFFFFFFF};

    u = (s - std::floor(s)) * width;
    v = (t - std::floor(t)) * width;

    texSample = bitmap[(int)u + (int)v*width];
    return texSample;
}
