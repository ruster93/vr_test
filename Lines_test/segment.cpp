#include "segment.h"
#include <cmath>
#define EPS 0.0001

Segment::Segment()
{
}
bool operator ==(Segment::Edge const & a, Segment::Edge const & b)
{
    return a.t == b.t;
}
bool operator <(Segment::Edge const & a, Segment::Edge const & b)
{
    return a.t < b.t;
}
void Segment::addSegment(double tStart, double tEnd)
{
    if(tStart < 0)
        tStart = 0;
    if(tEnd > 1)
        tEnd = 1;

    Edge start(tStart, true);
    Edge end(tEnd, false);

    segment.push_back(start);
    segment.push_back(end);
}

bool Segment::isFullSegment()
{
    segment.sort();

    std::list<Segment::Edge>::iterator p = segment.begin();
    int countStart = 0;

    if(segment.size() == 0 || std::abs(p->t) > EPS)
        return false;

    double nextT, nowT;
    while(p != segment.end())
    {
        if(p->isStart)
        {
            ++countStart;
            ++p;
        }
        else
        {
            --countStart;
            nowT = p->t;
            ++p;
            nextT = p->t;
            if(countStart == 0 && std::abs(nowT - 1) > EPS && p != segment.end() && std::abs(nextT - nowT) > EPS)
                return false;
        }


    }
    return true;
}
