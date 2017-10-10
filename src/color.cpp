#include "color.h"

color color::operator*(float multiplier)
{
    unsigned int alfa  = multiplier * (argb >> 24 & 255);
    unsigned int red   = multiplier * (argb >> 16 & 255);
    unsigned int green = multiplier * (argb >> 8  & 255);
    unsigned int blue  = multiplier * (argb       & 255);

    return {(alfa<<24)+(red<<16)+(green<<8)+(blue)};
}

color color::operator=(color value)
{
    this->argb = value.argb;
    return *this;
}

color color::operator=(unsigned int argb)
{
    this->argb = argb;
    return *this;
}

color color::operator+(color value)
{
    this->argb += value.argb;
    return *this;
}
