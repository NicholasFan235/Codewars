#include "Geometry.h"

double geometry::distance2(Point a, Point b){
    return std::pow(b.x-a.x, 2) + std::pow(b.y-a.y, 2);
}

double geometry::distance(Point a, Point b){
    return std::sqrt(distance2(a, b));
}

double geometry::dot(Line a, Line b){
    return a.x*b.x + a.y+b.y;
}

double geometry::cross(Line a, Line b){
    return 
}

double geometry::closestDistance(Circle c, Line l){
    
}
