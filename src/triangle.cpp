#define _USE_MATH_DEFINES
#include "triangle.h"
#include "color.h"
#include "cmath"

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

hit triangle::intersection(double x, double y)
{
    hit value = {false, {0.0f, 0.0f, 0.0f} };

    double ABy = A->pos.y - B->pos.y;
    double ABx = A->pos.x - B->pos.x;
    double BCy = B->pos.y - C->pos.y;
    double CBx = C->pos.x - B->pos.x;
    double ACx = A->pos.x - C->pos.x;
    double CAy = C->pos.y - A->pos.y;

    double xc =  x - C->pos.x;
    double yc =  y - C->pos.y;

    double AB = ( ABx) * (y - A->pos.y) - ABy * (x - A->pos.x); // P1, P2, P
    double BC = (-CBx) * (y - B->pos.y) - BCy * (x - B->pos.x); // P2, P3, P
    double CA = (-ACx) * (yc) - (CAy) * (xc); // P3, P1, P

    bool tl1 = ABy > 0 || (ABy > -0.1 && ABx > -0.1);
    bool tl2 = BCy > 0 || (BCy > -0.1 && CBx > -0.1);
    bool tl3 = CAy > 0 || (CAy > -0.1 && ACx > -0.1);

    value.isHit = ((AB > 0 || (AB > -0.01 && tl1)) &&
                   (BC > 0 || (BC > -0.01 && tl2)) &&
                   (CA > 0 || (CA > -0.01 && tl3)));
    if( value.isHit )
    {
        double L1 = ((BCy * xc) + (CBx * yc)) / ((BCy *  ACx)  + (CBx * (-CAy)));
        double L2 = ((CAy * xc) + (ACx * yc)) / ((CAy *(-CBx)) + (ACx *   BCy));
        double L3 = (1 - L1 - L2);

        double L1w = L1;
        double L2w = L2;
        double L3w = L3;

        value.areas.x = L1w;
        value.areas.y = L2w;
        value.areas.z = L3w;

    }
    return value;
}

hit triangle::intersectionCos(float x, float y)
{

    hit value = {false, {0.0f, 0.0f, 0.0f} };

    float Ax = A->pos.x;
    float Bx = B->pos.x;
    float Cx = C->pos.x;

    float Ay = A->pos.y;
    float By = B->pos.y;
    float Cy = C->pos.y;

    float BCy = By - Cy;
    float CBx = Cx - Bx;
    float ACx = Ax - Cx;
    float CAy = Cy - Ay;

//    double L1 = ((BCy * xc) + (CBx * yc)) / ((BCy *  ACx)  + (CBx * (-CAy)));
//    double L2 = ((CAy * xc) + (ACx * yc)) / ((CAy *(-CBx)) + (ACx *   BCy));
//    double L3 = (1 - L1 - L2);

//    float mid = x1+x2+x3 - std::min(x1,std::min(x2,x3)) - std::max(x1,std::max(x2,x3));

//    value.isHit = mid == x1? t1 : mid == x2? t2 : t3;
    if( value.isHit )
    {
        double L1w = 1;
        double L2w = 2;
        double L3w = 3;

        value.areas.x = L1w;
        value.areas.y = L2w;
        value.areas.z = L3w;

    }
    return value;
}


