#ifndef VERTEXPROCESSOR_H
#define VERTEXPROCESSOR_H
#include "mesh.h"
#include "light.h"
#include <vector>


class vertexProcessor
{
public:
    void setIdentity();

    void translate(float4 Tv);
    void rotate   (float a, float4 Rv);
    void scale    (float4 Sv);

    void lookAt(float4 up, float4 eye, float4 target);

    void perspective(float fov, float ratio, float near, float far);

    std::vector<vertex*> vertexBuffer;
    std::vector<light*>  lightBuffer;

    void transform();
private:
    mat4 M;
    mat4 V;
    mat4 P;

};

#endif // VERTEXPROCESSOR_H
