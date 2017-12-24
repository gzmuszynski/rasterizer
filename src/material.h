#ifndef MATERIAL_H
#define MATERIAL_H
#include "color.h"
#include "texture.h"
#include <string>
#include <map>
#include <vector>

#endif // MATERIAL_H

struct material
{
    std::string name;

    color ambient;
    color diffuse = {0xFFFFFFFF};
    color specular;
    color shininess;

    texture* ambientTexture;
    texture* diffuseTexture;
    texture* specularTexture;
    texture* shininessTexture;
};

