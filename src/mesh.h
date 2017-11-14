#ifndef MESH_H
#define MESH_H
#include "triangle.h"

struct mesh
{
    mesh(std::string filename);
    std::vector<vertex*> vertices;
    std::vector<triangle*> triangles;
};

#endif // MESH_H
