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
#include "line.h"

enum PenType {
    brush,
    eraser
};

class RenderArea : public QWidget, private Ui::RenderArea
{
    Q_OBJECT

public:
    explicit RenderArea(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    QPainter painter;
    QPen currentPen;
    QList<Line> lines;
    QPainterPath currentLine;
    PenType penType;

};

#endif // RENDERAREA_H
