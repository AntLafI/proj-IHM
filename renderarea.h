#ifndef RENDERAREA_H
#define RENDERAREA_H

#include "ui_renderarea.h"
#include <QMouseEvent>
#include <QPen>
#include <QMap>
#include <QPoint>
#include <QList>
#include <QPainter>
#include <QPainterPath>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include "line.h"

enum PenType {
    brush,
    eraser
};

class RenderArea : public QGraphicsView, private Ui::RenderArea
{
    Q_OBJECT

public:
    explicit RenderArea(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent  *event) override;
    void mouseMoveEvent(QMouseEvent  *event) override;
    void mouseReleaseEvent(QMouseEvent  *event) override;
    void paintEvent(QPaintEvent *event) override;
    void UpdateView();

private:
    QGraphicsView view;
    QList<QGraphicsItem *> itemList;
    QList<QPoint> currentShape;
    QGraphicsPolygonItem* currentItem;

    QPainter painter;
    QPen currentPen;
    QList<Line> lines;
    QPainterPath currentLine;
    PenType penType;
    int lastI;

};

#endif // RENDERAREA_H
