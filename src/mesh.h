#ifndef MESH_H
#define MESH_H
#include "triangle.h"
#include "texture.h"

struct mesh
{
    mesh(std::string filename, color col);
    mesh(float a, float b, float c);
    std::vector<vertex*> vertices;
    std::vector<triangle*> triangles;

    float4 Tv = {0.0f, 0.0f, 0.0f};
    float4 Rv = {0.0f, 0.0f, 0.0f};
    float4 Sv = {1.0f, 1.0f, 1.0f};

    std::map<std::string, material*> mtl(std::string filename);
};

std::vector<std::string> split(std::string string, char separator);

#endif // MESH_H
