#ifndef RENDERAREA_H
#define RENDERAREA_H

#include "ui_renderarea.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QMouseEvent>
#include <QPen>
#include <QImage>
#include <QVector>
#include <QSize>

class RenderArea : public QGraphicsView, private Ui::RenderArea
{
    Q_OBJECT

public:
    enum Tool { Freehand, Circle, Rect, Eraser };

    explicit RenderArea(QWidget *parent = nullptr);

    void setBackgroundImage(const QImage &img);
    void clearBackground();
    bool canUndo() const;
    bool canRedo() const;
    void renderToPainter(QPainter *p, const QSize &size) const;
    void setTool(Tool t);

public slots:
    void undo();
    void redo();

signals:
    void canUndoChanged(bool);
    void canRedoChanged(bool);
    void modified();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QPen currentPen;
    Tool m_tool = Freehand;

    QGraphicsPolygonItem *m_currentPoly = nullptr;
    QVector<QPointF> m_currentPolyPts;

    QGraphicsEllipseItem *m_currentEllipse = nullptr;
    QGraphicsRectItem   *m_currentRect = nullptr;
    QPointF m_pressScene;

    QGraphicsPixmapItem *m_bgItem = nullptr;

    struct Op {
        enum Kind { AddItem, RemoveItem } kind;
        QGraphicsItem *item = nullptr;
    };
    QVector<Op> m_undo;
    QVector<Op> m_redo;

    void pushAdd(QGraphicsItem *it);
    void pushRemove(QGraphicsItem *it);
    void notifyState();
    void eraseAt(const QPoint &viewPos);
};

#endif // RENDERAREA_H
