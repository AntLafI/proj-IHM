#include "renderarea.h"

#include <QColor>
#include <QPalette>
#include <QLine>
#include <QPaintDevice>
#include <QCursor>
#include <QPolygon>

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


    pen.setStyle(Qt::SolidLine);
    pen.setColor(Qt::green);
    pen.setWidth(10);


}

void RenderArea::mousePressEvent(QMouseEvent *event){
    qDebug() << "mouse pressed at pos " << event->pos();

    //if(event->source())
    pointList.append(event->pos());
    this->repaint();
}

void RenderArea::mouseMoveEvent(QMouseEvent *event){
    pointList.append(event->pos());
    this->repaint();
}

void RenderArea::paintEvent(QPaintEvent *event){
    painter.begin(this);
    painter.setPen(pen);
    QPolygon poly(pointList);
    painter.drawPoints(poly);
    painter.end();
}
