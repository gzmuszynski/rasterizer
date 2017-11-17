#include "triangle.h"
#include "color.h"
#include <sstream>

/*        C
 *       /\
 *      /  \
 *  AC /    \ BC
 *    /      \
 *   /________\
 *  A    AB    B
 */

triangle::triangle(vertex *A, vertex *B, vertex *C): A(A), B(B), C(C)
{

}

hit triangle::intersection(float x, float y)
{
    hit value = {false, {0.0f, 0.0f, 0.0f} };

    float BCy = B->pos.y - C->pos.y;
    float CBx = C->pos.x - B->pos.x;
    float ACx = A->pos.x - C->pos.x;
    float CAy = C->pos.y - A->pos.y;

    float xc =  x - C->pos.x;
    float yc =  y - C->pos.y;

    float AB = (A->pos.x - B->pos.x) * (y - A->pos.y) - (A->pos.y - B->pos.y) * (x - A->pos.x); // P1, P2, P
    float BC = (-CBx) * (y - B->pos.y) - (BCy) * (x - B->pos.x); // P2, P3, P
    float CA = (-ACx) * (yc) - (CAy) * (xc); // P3, P1, P

    value.isHit = AB >= 0 && BC >= 0 && CA >= 0;
    if( value.isHit )
    {
        float L1 = ((BCy * xc) + (CBx * yc)) / ((BCy *  ACx)  + (CBx * (-CAy)));
        float L2 = ((CAy * xc) + (ACx * yc)) / ((CAy *(-CBx)) + (ACx *   BCy));
        float L3 = 1 - L1 - L2;

        value.areas.x = L1;
        value.areas.y = L2;
        value.areas.z = L3;

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

vertex vertex::operator/=(float a)
{
    pos/=a;
    return *this;
}
