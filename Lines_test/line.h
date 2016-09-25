#ifndef LINE_H
#define LINE_H
#include "point.h"

class Line
{
public:
    Point start,end;

    Line(){}
    Line(Point start, Point end, bool ok = false);

    Point  getNormal();                            //нормаль отрезка
    Point  getDirection();                         //направление отрезка
    Line   subLine(double tStart, double tEnd);    //часть отрезка
    bool   isPoint();
    double length();
};

#endif // LINE_H
