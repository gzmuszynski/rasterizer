#ifndef TEXTURE_H
#define TEXTURE_H
#include "color.h"
#include <string>
enum FILTER : char {NEAREST, LINEAR};
enum WRAP   : char {CLAMP, REPEAT};

struct texture
{
    texture(std::string filename);

    color sample(float s, float t);

    color* bitmap;

    int width;
    int height;

    FILTER filter;
    WRAP wrap;
};

#endif // TEXTURE_H
