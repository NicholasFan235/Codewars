#ifndef CSTRUCT_INCLUDES
#define CSTRUCT_INCLUDES
#include "DefaultStructs.h"
#endif


struct Line{
    Point a, b;
    Line() : a(), b() {};
    Line(Point a, Point b) : a(a), b(b) {};
};