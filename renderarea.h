#ifndef RENDERAREA_H
#define RENDERAREA_H

#include "ui_renderarea.h"
#include <QMouseEvent>
#include <QPen>
#include <QPainter>

class RenderArea : public QWidget, private Ui::RenderArea
{
    Q_OBJECT

public:
    explicit RenderArea(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    //void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    QPainter painter;
    QPen pen;
    QList<QPoint> pointList;
};

#endif // RENDERAREA_H
