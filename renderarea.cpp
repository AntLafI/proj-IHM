#include "renderarea.h"

#include <QColor>
#include <QPalette>
#include <QLine>
#include <QPaintDevice>
#include <QCursor>
#include <QPolygon>
#include <QRandomGenerator64>
#include <QTransform>
#include <QBrush>

RenderArea::RenderArea(QWidget *parent)
    : QGraphicsView(parent)
{
    setupUi(this);
    setScene(new QGraphicsScene(this));

    setAlignment(Qt::AlignCenter);
    QColor col;
    col.setRgb(255,255,255);
    QPalette pal;
    setAutoFillBackground(true);
    pal.setColor(QPalette::Window, col);
    setPalette(pal);

    currentPen.setStyle(Qt::SolidLine);
    col.setRgb(255,0,0);
    currentPen.setColor(col);
    currentPen.setWidth(5);
}

void RenderArea::mousePressEvent(QMouseEvent *event){

    //Line currentLine ;
    //currentLine.setWidth(5);


    switch(event->button()){
    case Qt::RightButton:

        penType = eraser;
        /*
        if(penType == brush){

            QPolygon newPoly(currentPath);
            QGraphicsPolygonItem graphicsPoly(newPoly);
            QBrush brush(Qt::SolidLine);

            graphicsPoly.setPolygon(newPoly);
            graphicsPoly.setPen(currentPen);
            graphicsPoly.setBrush(brush);

            itemList.append(&graphicsPoly);

            qDebug() << "eraser mode";
        }
        else{
            penType = eraser;
        }*/

        break;
    //case Qt::LeftButton:
    default:
        if(penType == brush){
            qDebug() << event->pos();
            currentShape << event->pos();
            qDebug() << currentShape;
            currentItem->setPolygon(QPolygon(currentShape));

        }
        else{
            QPolygon newPoly;
            QBrush brush(Qt::SolidLine);
            newPoly << event->pos();
            currentItem = new QGraphicsPolygonItem(QPolygon(newPoly));
            currentShape = newPoly.toList();
            currentItem->setPen(currentPen);
            currentItem->setBrush(brush);
            scene()->addItem(currentItem);
            penType = PenType::brush;
            qDebug() << "brush mode";
        }
        break;
    }



    //int rnd = QRandomGenerator::global()->bounded(3);
    QGraphicsView::mousePressEvent(event);
    /*
    switch(event->button()){
    case Qt::RightButton:
        penType = eraser;
        currentLine.setColor(Qt::transparent);
        break;
    case Qt::LeftButton:
        penType = brush;
        currentLine.setColor(rnd < 2 ? rnd < 1 ? Qt::red : Qt::green : Qt::blue);
        break;
    default:
        penType = brush;
        currentLine.setColor(rnd < 2 ? rnd < 1 ? Qt::red : Qt::green : Qt::blue);
        break;
    }
    lines.append(currentLine);*/
}

void RenderArea::mouseMoveEvent(QMouseEvent *event){
    QGraphicsView::mouseMoveEvent(event);
    if(penType == eraser)
        scene()->removeItem(scene()->itemAt(event->pos(), transform()));

    /*
    int sizeBefore = lines.back().getPoints().size();


    if(!lines.back().getPoints().contains(event->pos())) lines.back().addPoint(event->pos());
    if(sizeBefore != lines.back().getPoints().size()) this->update();*/
}

void RenderArea::mouseReleaseEvent(QMouseEvent *event){
    QGraphicsView::mouseReleaseEvent(event);
}


void RenderArea::paintEvent(QPaintEvent *event){
    QGraphicsView::paintEvent(event);
    /*
    for(int i = 0; i < itemList.size(); i++){

        this->scene()->addItem(itemList[i]);
    }
    QGraphicsPolygonItem lastPath;
    QPolygon newPoly(currentPath);
    lastPath.setPolygon(newPoly);
    lastPath.setPen(currentPen);
    QBrush brush(Qt::SolidLine);
    lastPath.setBrush(brush);
    this->scene()->addItem(&lastPath);



    //scene.
    /*
    for(int i = 0; i < lines.size(); i++){
        QPen pen;
        QColor penColor;
        if(lines.at(i).getColor() == Qt::transparent){
            penColor = this->palette().window().color();
        }
        else{
            penColor = lines.at(i).getColor();
        }
        pen.setColor(penColor);
        pen.setWidth(lines.at(i).getWidth());
        pen.setStyle(Qt::SolidLine);
        painter.setPen(pen);
        QPolygon poly(lines.at(i).getPoints());
        painter.drawPolyline(poly);
    }*/
}


void RenderArea::UpdateView(){
    /*
    for(int i = 0; i < itemList.size(); i++){

        scene.addItem(itemList[i]);
    }
    QGraphicsPolygonItem lastPath;
    QPolygon newPoly(currentPath);
    lastPath.setPolygon(newPoly);
    lastPath.setPen(currentPen);
    QBrush brush(Qt::SolidLine);
    lastPath.setBrush(brush);
    scene.addItem(&lastPath);
*/
    //scene.
    /*
    for(int i = 0; i < lines.size(); i++){
        QPen pen;
        QColor penColor;
        if(lines.at(i).getColor() == Qt::transparent){
            penColor = this->palette().window().color();
        }
        else{
            penColor = lines.at(i).getColor();
        }
        pen.setColor(penColor);
        pen.setWidth(lines.at(i).getWidth());
        pen.setStyle(Qt::SolidLine);
        painter.setPen(pen);
        QPolygon poly(lines.at(i).getPoints());
        painter.drawPolyline(poly);
    }*/
}
