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

    float ABy = A->pos.y - B->pos.y;
    float ABx = A->pos.x - B->pos.x;
    float BCy = B->pos.y - C->pos.y;
    float CBx = C->pos.x - B->pos.x;
    float ACx = A->pos.x - C->pos.x;
    float CAy = C->pos.y - A->pos.y;

    float xc =  x - C->pos.x;
    float yc =  y - C->pos.y;

    double AB = ( ABx) * (y - A->pos.y) - ABy * (x - A->pos.x); // P1, P2, P
    double BC = (-CBx) * (y - B->pos.y) - BCy * (x - B->pos.x); // P2, P3, P
    double CA = (-ACx) * (yc) - (CAy) * (xc); // P3, P1, P

    bool tl1 = ABy > 0 || (ABy == 0 && ABx < 0);
    bool tl2 = BCy > 0 || (BCy == 0 && CBx > 0);
    bool tl3 = CAy > 0 || (CAy == 0 && ACx > 0);

    value.isHit = ((AB > 0 || (AB == 0 && tl1)) &&
                   (BC > 0 || (BC == 0 && tl2)) &&
                   (CA > 0 || (CA == 0 && tl3)));
    if( value.isHit )
    {
        double L1 = ((BCy * xc) + (CBx * yc)) / ((BCy *  ACx)  + (CBx * (-CAy)));
        double L2 = ((CAy * xc) + (ACx * yc)) / ((CAy *(-CBx)) + (ACx *   BCy));
        double L3 = 1 - L1 - L2;

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
