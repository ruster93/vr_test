#ifndef CIRUS_H
#define CIRUS_H
#include <vector>
#include "line.h"

class Cirus
{
public:
    Line edges[3];                   //вспомогательные отрезки, образующие угол обзора

    std::vector<Line> lines;
    Line checkingLine;               //особый (красный) отрезок

    Cirus(){}

    void addLine(Line line);

    bool  addCheckingLine(Line line); //добавление особого (красного) отрезка
    bool  isVisible();                //проверка видимости особого отрезка

    std::vector<Line> lineClipping(); //поиск и отсечение отрезков, попадающих в угол обзора
};

#endif // CIRUS_H
