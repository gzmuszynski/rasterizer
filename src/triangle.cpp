#include "triangle.h"


hit triangle::intersection(float x, float y)
{
    hit value = {false, {0.0f, 0.0f, 0.0f} };

    float AB = (x - A.x) * (B.y - A.y) - (B.x - A.x) * (y - A.y); // P1, P2, P
    float BC = (x - B.x) * (C.y - B.y) - (C.x - B.x) * (y - B.y); // P2, P3, P
    float CA = (x - C.x) * (A.y - C.y) - (A.x - C.x) * (y - C.y); // P3, P1, P

    value.isHit = AB > 0 && BC > 0 && CA > 0;
    if( value.isHit )
    {
        float Area = 1.0/((C.x - A.x) * (B.y - A.y) - (B.x - A.x) * (C.y - A.y));
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
