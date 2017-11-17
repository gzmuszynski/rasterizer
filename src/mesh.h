#ifndef MESH_H
#define MESH_H
#include "triangle.h"

struct mesh
{
    mesh(std::string filename);
    mesh(float a, float b, float c);
    std::vector<vertex*> vertices;
    std::vector<triangle*> triangles;

    float4 Tv = {0.0f, 0.0f, 0.0f};
    float4 Rv = {0.0f, 0.0f, 0.0f};
    float4 Sv = {1.0f, 1.0f, 1.0f};
};

#endif // MESH_H
