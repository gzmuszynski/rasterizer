#include "fragmentprocessor.h"

void fragmentProcessor::fillTriangle(buffer &buf)
{
    float stepx = 1.0/buf.width;
    float stepy = 1.0/buf.height;

    float maxx, minx, maxy, miny;  // min-max for basic rendertime saving
    minmax(minx, miny, maxx, maxy);

    // check for intersection

    for(float x = minx; x < maxx; x += stepx)
    {
        for(float y = miny; y < maxy; y += stepy)
        {
            hit test = tri->intersection( x, y );
            if(test.isHit)
            {
                float depth = (tri->A->pos.z * test.areas.x) + (tri->B->pos.z * test.areas.y) + (tri->C->pos.z * test.areas.z);

                if(depth >= 0 && depth <= 1)
                {
                    int x1 = (x+1) * buf.width * 0.5f, y1 = (y+1) * buf.height * 0.5f;
                    bool test2 = (depth < buf.depth[(int)(buf.width * y1 + x1)]);
                    bool test3 = buf.depth[(int)(buf.width * y1 + x1)] == 1;
                    if(test2 || test3 || !depthTestEnabled)
                    {
                        color pixel = shader(test);

                        buf.write(x1,y1 , pixel, depth);
                    }
                }
            }
        }
    }
}

color fragmentProcessor::shader(hit test)
{
    color ambMat = (tri->A->col*test.areas[0] + tri->B->col*test.areas[1] + tri->C->col*test.areas[2]);
    color final = {0xFF000000};
    color ambient = {0}, diffuse = {0}, specular = {0};

    float4 point (tri->A->pos  * test.areas[0] + tri->B->pos  * test.areas[1] + tri->C->pos  * test.areas[2]);
    float4 normal(tri->A->norm * test.areas[0] + tri->B->norm * test.areas[1] + tri->C->norm * test.areas[2]);
    normal = normal.normalize();

    for(int i = 0; i < lights.size(); i++)
    {
        light *l1 = lights[i];

        ambient + l1->ambient;

        float4 lightVec = l1->getVector(point).normalize();

        float LdotN = std::min(float4::dotProduct( lightVec, normal),1.0f);
        diffuse + (ambMat * l1->diffuse * std::max(0.0f,LdotN)); // lambertian

        specular + l1->specular;
        final = final + ambient + diffuse + specular;
    }
//                final = (color{0xFFFFFFFF} * ((normal*float4(0.5,0.5,0.5,1))+float4(0.5,0.5,0.5,0))); // normal viewing debug
    //            diffuse = (color{0xFFFFFFFF} * ((point*float4(0.5,0.5,1.0,1))+float4(0.5,0.5,0.0,0))); // point viewing debug


    return final;
}

void fragmentProcessor::minmax(float &minx, float &miny, float &maxx, float &maxy)
{
    maxy = (tri->A->pos.y > tri->B->pos.y ) ? tri->A->pos.y : tri->B->pos.y;
    maxx = (tri->A->pos.x > tri->B->pos.x ) ? tri->A->pos.x : tri->B->pos.x;
    minx = (tri->A->pos.x < tri->B->pos.x ) ? tri->A->pos.x : tri->B->pos.x;
    miny = (tri->A->pos.y < tri->B->pos.y ) ? tri->A->pos.y : tri->B->pos.y;

    maxx = (maxx > tri->C->pos.x ) ? maxx : tri->C->pos.x;
    minx = (minx < tri->C->pos.x ) ? minx : tri->C->pos.x;
    maxy = (maxy > tri->C->pos.y ) ? maxy : tri->C->pos.y;
    miny = (miny < tri->C->pos.y ) ? miny : tri->C->pos.y;

    maxx>1? maxx = 1: maxx<-1? maxx = -1: true;
    maxy>1? maxy = 1: maxy<-1? maxy = -1: true;

    minx>1? minx = 1: minx<-1? minx = -1: true;
    miny>1? miny = 1: miny<-1? miny = -1: true;

    //    maxx =  1.0f; maxy =  1.0f;
    //    minx = -1.0f; miny = -1.0f;
}
