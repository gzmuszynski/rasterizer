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
    wrap = CLAMP;
    filter = LINEAR;
}

color texture::sample(float s, float t)
{
    color texSample = color{0xFFFFFFFF};

    float u,v;

    if(height == 0 || width == 0)
        return color{0xFFFFFFFF};

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
        float uR = u-std::floor(u);
        float vR = v-std::floor(v);
        float uR1 = 1-uR;
        float vR1 = 1-vR;

        int u1,v1;
        if(wrap == CLAMP)
        {
            u1 = std::max(0.0f,std::min(u-1, width-1.0f));
            v1 = std::max(0.0f,std::min(v-1,height-1.0f));
        }
        if(wrap == REPEAT)
        {
            u1 = u-1; u1 %= width;
            v1 = v-1; v1 %= height;
        }
        color texSample11 = bitmap[(int)u + (int)v*width] * uR;
        color texSample12 = bitmap[(int)u + (int)v1*width] * uR;
        color texSample21 = bitmap[(int)u1 + (int)v*width] * uR1;
        color texSample22 = bitmap[(int)u1 + (int)v1*width] * uR1;

        texSample = (texSample11 + texSample21)*vR + (texSample12 + texSample22) * vR1;
    }
    return texSample;
}
