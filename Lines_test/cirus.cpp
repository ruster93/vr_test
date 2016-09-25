#include "cirus.h"
#include <cmath>
#include <list>
#include "segment.h"
#define EPS 0.0001

void Cirus::addLine(Line line)
{
    if(!line.isPoint())
        lines.push_back(line);
}

bool Cirus::addCheckingLine(Line line)
{
    if(line.isPoint() ||
       (std::abs(line.start.x) < EPS && std::abs(line.start.y) < EPS)||
       (std::abs(line.end.x) < EPS && std::abs(line.end.y) < EPS))
        return false;

    checkingLine = line;

    Point x, y, z;
    x = Point(0, 0);

    y = line.start;
    z = line.end;

    if(Point::cross(Point::sub(y, x), Point::sub(z, x)) > 0) // обход угла обзора против часовой
        std::swap(y, z);

    edges[0] = Line(x, y, true);
    edges[1] = Line(y, z, true);
    edges[2] = Line(z, x, true);
    return true;
}

std::vector<Line> Cirus::lineClipping()
{
    std::vector<Line> result;

    for(int i = 0;i < lines.size(); ++i)
    {
       Point direction = lines[i].getDirection(); //направление отрезка
       Point normal;                              //нормаль ребра угла обзора
       Point normalCentr;                         //центр нормали

       double tStart = 0, tEnd = 1, dotDN, t = 0, Q;
       for(int j = 0; j < 3; ++j)
       {
           normal = edges[j].getNormal();
           dotDN  = Point::dot(normal, direction); //скалярное произведение нормали и направления
           normalCentr =  Point::add(edges[j].start, Point::mul(Point::sub(edges[j].end, edges[j].start), 0.5));

           Q = Point::dot(Point::sub(lines[i].start, normalCentr), normal);

           if(std::abs(dotDN)<EPS)                 // отрезок параллелен ребру
           {
               if(Q >= 0)
                result.push_back(lines[i]);
           }
           else
           {

               t = - Q / dotDN;

                if(dotDN > 0)                      // отрезок снаружи внутрь
                {
                    if(t > tStart)
                        tStart = t;
                }
                else                               // отрезок изнутри наружу
                {
                    if(t < tEnd)
                        tEnd = t;
                }
           }
       }

       if(tStart < tEnd)
       {
           result.push_back(lines[i].subLine(tStart, tEnd));
       }
    }
    return result;
}

bool Cirus::isVisible()
{
    std::vector<Line> clipLines = lineClipping();   // отсеченные отрезки
    Segment segment;                                // границы перекрываемых частей особого отрезка

    for (int i = 0; i < clipLines.size(); ++i)      // поиск точек пересечения лучей, проходящих через точки перекрывающих отрезков, и особого отрезка
    {
        double k, tStart = 0, tEnd = 1;
        double x0,y0,x1,y1;
        x0 = checkingLine.start.x;
        y0 = checkingLine.start.y;
        x1 = checkingLine.end.x;
        y1 = checkingLine.end.y;

        if(std::abs(clipLines[i].start.x) > EPS)
        {
            k = clipLines[i].start.y / clipLines[i].start.x;
            tStart = -(y0 - x0 * k)/((y1 - y0) - (x1 - x0) * k);

        }
        else if(std::abs(clipLines[i].start.y) > EPS)
        {
            k = clipLines[i].start.x / clipLines[i].start.y;
            tStart = -(x0 - y0 * k)/((x1 - x0) - (y1 - y0) * k);
        }


        if(std::abs(clipLines[i].end.x) > EPS)
        {
            k = clipLines[i].end.y / clipLines[i].end.x;
            tEnd = -(y0 - x0 * k)/((y1 - y0) - (x1 - x0) * k);

        }
        else if(std::abs(clipLines[i].end.y) > EPS)
        {
            k = clipLines[i].end.x / clipLines[i].end.y;
            tEnd = -(x0 - y0 * k)/((x1 - x0) - (y1 - y0) * k);
        }
        if(tEnd < tStart)
            std::swap(tStart, tEnd);

        segment.addSegment(tStart, tEnd); // добавление перекрываемой части особого отрезка
    }
    return !segment.isFullSegment();
}
