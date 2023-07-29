#ifndef GEOMETRY_INCLUDES
#define GEOMETRY_INCLUDES
#include "CustomStructs.h"
#include "DefaultStructs.h"
#include <math.h>
#endif

namespace geometry{
    double distance(Point a, Point b);
    double distance2(Point a, Point b);
    double dot(Line a, Line b);
    double cross(Line a, Line b);
    double closestDistance(Circle c, Line l);
    double angle(Circle c, Point p);
    double angle(Line a, Line b);
}