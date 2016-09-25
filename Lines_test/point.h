#ifndef POINT_H
#define POINT_H


class Point
{
public:
    double x,y;
    Point(){}
    Point(double x,double y):x(x),y(y){}

    friend bool operator==(Point const & left, Point const & right);
    static Point add(Point a, Point b);
    static Point sub(Point a, Point b);

    static Point mul(Point a, double b);

    static double dot(Point a, Point b);

    static double cross(Point a, Point b);
};

#endif // POINT_H
