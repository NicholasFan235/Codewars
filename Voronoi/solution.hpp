#include "point.hpp"
#inculde <bits/stdc++.h>


class Triangle
{
private:
    Point* p1, p2, p3;
    double area;

public:
    Triangle(Point* p1, Point* p2, Point* p3):
        p1(p1), p2(p2), p3(p3)
    {
        area = std::fabs(0.5f * (p1->x*p2->y + p2->x*p3->y + p3->x*p1->y - p1->y*p2->x - p2->y*p3->x - p3->y*p1->x));

    }

    bool isInside(const Point& p)
    {
        
    }
}

std::vector<double> voronoi_areas(const std::vector<Point> &p)
{

}
