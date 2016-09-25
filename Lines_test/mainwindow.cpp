#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>

#include<QMessageBox>

#include "cirus.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(700,700);
    this->setFixedSize(700,700);

    scene = new QGraphicsScene();

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scene->setSceneRect(-260,-260,520,520);

    reDraw();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    reDraw();

}

void MainWindow::reDraw()
{

    scene->clear();

    scene->addLine(-250,0,250,0,QPen(Qt::yellow));   // горизонтальная линия через центр
    scene->addLine(0,-250,0,250,QPen(Qt::yellow));   // вертикальная линия через центр


    Cirus cirus;
    int maxLength = 50;                              // максимальная длина отрезков
    int randLength = maxLength * 2;                  // для rand
    int size = 10;                                   // количество отрезков отрезков

    for(int i = 0; i < size; ++i)
    {
        cirus.addLine(Line(Point(rand()%randLength - maxLength, rand()%randLength - maxLength), Point(rand()%randLength - maxLength, rand()%randLength - maxLength)));
    }

    if(!cirus.addCheckingLine(Line(Point(rand()%randLength - maxLength, rand()%randLength - maxLength), Point(rand()%randLength - maxLength, rand()%randLength - maxLength))))
        return; // выходит из точки (0;0) или является точкой

    int x0,y0,x1,y1;
    int pixelX = 5;
    int pixelY = -5;

    //отрисовка отрезков
    for(int i = 0 ; i < size; ++i)
    {
        x0 = cirus.lines[i].start.x * pixelX;
        y0 = cirus.lines[i].start.y * pixelY;
        x1 = cirus.lines[i].end.x * pixelX;
        y1 = cirus.lines[i].end.y * pixelY;

        scene->addLine(x0,y0,x1,y1,QPen(Qt::black));
    }

    //отрисовка граней угла оьзора
    for(int i = 0 ; i < 3; ++i)
    {
        x0 = cirus.edges[i].start.x * pixelX;
        y0 = cirus.edges[i].start.y * pixelY;
        x1 = cirus.edges[i].end.x * pixelX;
        y1 = cirus.edges[i].end.y * pixelY;
        scene->addLine(x0,y0,x1,y1,QPen(QColor(100,190,0)));
    }

    //отрисовка особого отрезка
    x0 = cirus.checkingLine.start.x * pixelX;
    y0 = cirus.checkingLine.start.y * pixelY;
    x1 = cirus.checkingLine.end.x * pixelX;
    y1 = cirus.checkingLine.end.y * pixelY;
    scene->addLine(x0,y0,x1,y1,QPen(QColor(100,100,255)));

    std::vector<Line> lines = cirus.lineClipping();

    //отрисовка отсеченных отрезков
    for(int i = 0 ; i < lines.size(); ++i)
    {
        x0 = lines[i].start.x * pixelX;
        y0 = lines[i].start.y * pixelY;
        x1 = lines[i].end.x * pixelX;
        y1 = lines[i].end.y * pixelY;

        scene->addLine(x0,y0,x1,y1,QPen(Qt::red));
    }

    bool check = cirus.isVisible();
    QMessageBox msgBox;
      msgBox.setText(check ? "Видим" : "Не видим");
      msgBox.exec();

}
