#include "color.h"



color color::operator*(color value)
{
    float div = 1.0f/255;

    float a = value.alfa() *div * alfa();
    float r = value.red()  *div * red();
    float g = value.green()*div * green();
    float b = value.blue() *div * blue();

    return {((unsigned int)a<<24)+((unsigned int)r<<16)+((unsigned int)g<<8)+((unsigned int)b)};
}

color color::operator*(float multiplier)
{
    unsigned int a = multiplier * alfa();
    unsigned int r = multiplier * red();
    unsigned int g = multiplier * green();
    unsigned int b = multiplier * blue();

    return {(a<<24)+(r<<16)+(g<<8)+(b)};
}

color color::operator*(float4 v)
{
    unsigned int a = v.w * alfa();
    unsigned int r = v.x * red();
    unsigned int g = v.y * green();
    unsigned int b = v.z * blue();

    return {(a<<24)+(r<<16)+(g<<8)+(b)};
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
    float div = 1.0f/2;

    float a = ((float)value.alfa() + alfa() );
    float r = ((float)value.red()  + red()  );
    float g = ((float)value.green()+ green());
    float b = ((float)value.blue() + blue() );

    a = std::min(255.0f,std::max(0.0f,a));
    r = std::min(255.0f,std::max(0.0f,r));
    g = std::min(255.0f,std::max(0.0f,g));
    b = std::min(255.0f,std::max(0.0f,b));

    this->argb = ((unsigned int)a<<24)+((unsigned int)r<<16)+((unsigned int)g<<8)+((unsigned int)b);
    return *this;
}
