#include "serializer.h"
#include <fstream>


void serializer::bufferToTGA(buffer buf)
{
    unsigned char header[18] = {0};

    header[2]  = 2;
    header[12] = buf.width         & 0xFF;
    header[13] = (buf.width >> 8)  & 0xFF;
    header[14] = buf.height        & 0xFF;
    header[15] = (buf.height >> 8) & 0xFF;
    header[16] = 32;

    std::ofstream file("render.tga",std::ios::binary);

    if(!file) return;

    file.write((const char*)&header, 18);

    for(int y = 0; y < buf.height; y++)
        {
        for(int x = 0; x < buf.width; x++)
            {
                unsigned int color = buf.color[(buf.width*y)+x];
//                unsigned int color = 0xFFFFFFFF;
                file.write((const char*)&color, sizeof(unsigned int));
            }
        }
    file.close();
}
