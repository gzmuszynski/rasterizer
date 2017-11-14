#ifndef COLOR_H
#define COLOR_H



struct color{
    unsigned int argb;

    color operator*(float multiplier);
    color operator=(color value);
    color operator=(unsigned int argb);
    color operator+(color value);

};
#endif // COLOR_H
