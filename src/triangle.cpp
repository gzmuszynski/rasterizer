#include "triangle.h"

triangle::triangle(vec3 p1, vec3 p2, vec3 p3, unsigned int color):
    p1(p1),
    p2(p2),
    p3(p3),
    color(color)
{

}

bool triangle::intersection(float x, float y)
{

    float e1 = (x - p2.x) * (p1.y - p2.y) - (p1.x - p2.x) * (y - p2.y);
    float e2 = (x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (y - p3.y);
    float e3 = (x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (y - p1.y);

    if( e1 > 0 && e2 > 0 && e3 > 0)
    {
        return true;
    }
    return false;
}

vec3 triangle::intersection(vec3 point)
{
    return {0.0,0.0,0.0};
}
