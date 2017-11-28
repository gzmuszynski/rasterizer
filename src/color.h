#ifndef COLOR_H
#define COLOR_H
#include "maths.h"

struct color{
    unsigned int argb;

    color operator*(color value);
    color operator*(float multiplier);
    color operator*(float4 v);
    color operator=(color value);
    color operator=(unsigned int argb);
    color operator+(color value);

    unsigned int alfa()  {return (argb >> 24 & 255);}
    unsigned int red()   {return (argb >> 16 & 255);}
    unsigned int green() {return (argb >> 8  & 255);}
    unsigned int blue()  {return (argb       & 255);}

};
#endif // COLOR_H
