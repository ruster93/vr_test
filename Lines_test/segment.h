#ifndef SEGMENT_H
#define SEGMENT_H
#include <list>

class Segment
{
public:
    struct Edge
    {
        double t;
        bool isStart;               // начало границы или нет
        Edge(double t, bool isStart):t(t),isStart(isStart){}
    };
    Segment();

    std::list<Edge> segment;                    //границы перекрываемых частей особого отрезка
    void addSegment(double tStart, double tEnd);
    bool isFullSegment();                       // полное покрытие отрезка [0;1]
};

#endif // SEGMENT_H
