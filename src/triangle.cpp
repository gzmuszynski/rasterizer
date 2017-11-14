#include "triangle.h"
#include "color.h"
#include <sstream>


triangle::triangle(vertex *A, vertex *B, vertex *C): A(A), B(B), C(C)
{

}

hit triangle::intersection(float x, float y)
{
    hit value = {false, {0.0f, 0.0f, 0.0f} };

    float AB = (x - A->pos.x) * (B->pos.y - A->pos.y) - (B->pos.x - A->pos.x) * (y - A->pos.y); // P1, P2, P
    float BC = (x - B->pos.x) * (C->pos.y - B->pos.y) - (C->pos.x - B->pos.x) * (y - B->pos.y); // P2, P3, P
    float CA = (x - C->pos.x) * (A->pos.y - C->pos.y) - (A->pos.x - C->pos.x) * (y - C->pos.y); // P3, P1, P

    value.isHit = AB > 0 && BC > 0 && CA > 0;
    if( value.isHit )
    {
        float Area = 1.0/((C->pos.x - A->pos.x) * (B->pos.y - A->pos.y) - (B->pos.x - A->pos.x) * (C->pos.y - A->pos.y));
        value.areas.x = BC*Area;
        value.areas.y = CA*Area;
        value.areas.z = AB*Area;

    }
    return value;
}

//bool edgeFunction(const Vec2f &a, const Vec3f &b, const Vec2f &c)
//{
//return ((c.x - a.x) * (b.y - a.y) - (b.x - a.x) * (c.y - a.y)>= 0);
//}

std::vector<std::string> split(std::string string, char separator)
{
    std::stringstream test(string);
    std::string segment;
    std::vector<std::string> seglist;

    while(std::getline(test, segment, separator))
    {
        seglist.push_back(segment);
    }

    return seglist;
}

vertex vertex::operator*=(mat4 matrix)
{
    pos*=matrix;
    return *this;
}
