#ifndef TRIANGLE_H
#define TRIANGLE_H

struct vec3
{
    float x,y,z;
};

struct triangle
{
    triangle(vec3 p1, vec3 p2, vec3 p3, unsigned int color);
    vec3 p1,p2,p3;

    unsigned int color = 0x000000;

    bool intersection(float x, float y);
    vec3 intersection(vec3 point);
};

#endif // TRIANGLE_H
