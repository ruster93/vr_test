#include "point.h"


bool operator==(const Point &left, const Point &right)
{
    return left.x == right.x && left.y == right.y;
}

Point Point::add(Point a, Point b)
{
    return Point(a.x + b.x, a.y + b.y);
}

Point Point::sub(Point a, Point b)
{
    return Point(a.x - b.x, a.y - b.y);
}

Point Point::mul(Point a, double b)
{
    return Point(a.x * b, a.y * b);
}

double Point::dot(Point a, Point b)
{
    return a.x * b.x + a.y * b.y;
}

double Point::cross(Point a, Point b)
{
    return a.x * b.y - a.y * b.x;
}
