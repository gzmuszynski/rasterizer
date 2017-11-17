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

    std::ofstream colorFile("render.tga",      std::ios::binary); // open files
    std::ofstream depthFile("renderDepth.tga", std::ios::binary); // for writing

    if(!colorFile) return;

    colorFile.write((const char*)&header, 18); // write header
    depthFile.write((const char*)&header, 18); // to files

    for(int y = 0; y < buf.height; y++)
        {
        for(int x = 0; x < buf.width; x++)
            {
                color diffuse = buf.diffuse[(buf.width*y)+x];           // color data extraction in 0xAARRGGBB format
                unsigned int dint = 127 - (127* buf.depth[(buf.width*y)+x]);    // depth float to unsigned int cast
                unsigned int depth = dint+(dint<<8)+(dint<<16)+(dint<<24); // depth unsigned int to 0xAARRGGBB construction

                colorFile.write((const char*)&diffuse, sizeof(unsigned int)); // write color to file
                depthFile.write((const char*)&depth, sizeof(unsigned int)); // write depth to file
            }
        }
    colorFile.close();
}
