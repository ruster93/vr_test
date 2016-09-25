#include "line.h"
#include <cmath>

Line::Line(Point start, Point end, bool ok)
{
    if(start.x < end.x || ok)       //упорядочивание направления
    {
        this->start = start;
        this->end   = end;
    }
    else if(start.x == end.x)
    {
        if(start.y > end.y)
        {
            this->start = end;
            this->end   = start;
        }
        else
        {
            this->start = start;
            this->end   = end;
        }
    }
    else
    {
        this->start = end;
        this->end   = start;
    }
}

Point Line::getNormal()
{
    return Point(end.y - start.y, start.x-end.x);
}

Point Line::getDirection()
{
    return Point(end.x - start.x, end.y-start.y);
}

Line Line::subLine(double tStart, double tEnd)
{
    Point newStart = Point::add(start, Point::mul(Point::sub(end, start), tStart));
    Point newEnd   = Point::add(start, Point::mul(Point::sub(end, start), tEnd));

    return Line(newStart, newEnd);
}

bool Line::isPoint()
{
    return this->start == this->end;
}

double Line::length()
{
    return sqrt(Point::dot(getDirection(),getDirection()));
}

