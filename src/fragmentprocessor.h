#ifndef FRAGMENTPROCESSOR_H
#define FRAGMENTPROCESSOR_H

#include "mesh.h"
#include "buffer.h"

class fragmentProcessor
{
public:
    void fillTriangle(buffer &buf);

    triangle* tri;
    std::vector<light*> lights;

private:
    bool depthTestEnabled = true;

    color shader(hit test);

    void minmax(float &minx, float &miny, float &maxx, float &maxy);


//    image* texture;

};

#endif // FRAGMENTPROCESSOR_H
