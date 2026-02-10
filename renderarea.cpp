#include "renderarea.h"

#include <QColor>
#include <QPalette>
#include <QLine>
#include <QPaintDevice>
#include <QCursor>
#include <QPolygon>
#include <QRandomGenerator64>

RenderArea::RenderArea(QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);
    QColor col;
    col.setRgb(255,255,255);
    QPalette pal;
    setAutoFillBackground(true);
    pal.setColor(QPalette::Window, col);
    setPalette(pal);
}

void RenderArea::mousePressEvent(QMouseEvent *event){
    qDebug() << "mouse at" << event->pos() << "button" << event->button();/*
    lines.append(QPainterPath());
    QPainterPath path = lines.back();
    path.moveTo(event->pos());
    */

    Line currentLine ;
    currentPen.setStyle(Qt::SolidLine);
    currentLine.setWidth(5);

    int rnd = QRandomGenerator::global()->bounded(2);
    switch(event->button()){
    case Qt::RightButton:
        penType = eraser;
        currentLine.setColor(Qt::transparent);
        //currentPen.setColor(Qt::transparent);
        break;
    case Qt::LeftButton:
        penType = brush;
        currentLine.setColor(rnd < 2 ? rnd < 1 ? Qt::red : Qt::green : Qt::blue);
        //currentPen.setColor(rnd < 2 ? rnd < 1 ? Qt::red : Qt::green : Qt::blue);
        break;
    default:
        penType = brush;
        currentLine.setColor(rnd < 2 ? rnd < 1 ? Qt::red : Qt::green : Qt::blue);
        //currentPen.setColor(rnd < 2 ? rnd < 1 ? Qt::red : Qt::green : Qt::blue);
        break;
    }
    lines.append(currentLine);
}

void RenderArea::mouseMoveEvent(QMouseEvent *event){
    qDebug() << "mouse at" << event->pos() << "button" << event->button();
    int sizeBefore = lines.back().getPoints().size();


    if(!lines.back().getPoints().contains(event->pos())) lines.back().addPoint(event->pos());
    if(sizeBefore != lines.back().getPoints().size()) this->update();
}

void RenderArea::mouseReleaseEvent(QMouseEvent *event){
    //lines.back().closeSubpath();
}

void RenderArea::paintEvent(QPaintEvent *event){
    painter.begin(this);


    for(int i = 0; i < lines.size(); i++){
        QPen pen;
        pen.setColor(lines.at(i).getColor());
        pen.setWidth(lines.at(i).getWidth());
        pen.setStyle(Qt::SolidLine);
        painter.setPen(pen);
        QPolygon poly(lines.at(i).getPoints());
        painter.drawPolyline(poly);
    }

    painter.end();
}
