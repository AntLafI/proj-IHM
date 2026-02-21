#ifndef RENDERAREA_H
#define RENDERAREA_H

#include "ui_renderarea.h"
#include <QMouseEvent>
#include <QPen>
#include <QPainter>
#include <QImage>
#include <QPolygon>
#include <QVector>
#include <QSize>
#include <QList>
#include <QRect>

class RenderArea : public QWidget, private Ui::RenderArea
{
    Q_OBJECT

public:
    enum Tool { Freehand, Circle, Eraser };

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
    void paintEvent(QPaintEvent *event) override;

private:
    QPainter painter;
    QPen pen;
    QList<QPoint> pointList;
    QImage m_background;
    QPolygon m_currentStroke;
    QVector<QPolygon> m_strokes;
    QVector<QPolygon> m_redoStrokes;

    Tool m_tool = Freehand;

    QSize m_baseSize;

    QPoint m_pressPos;
    QRect m_currentCircle;
    QVector<QRect> m_circles;
    QVector<QRect> m_redoCircles;

    struct EraseOp {
        enum Kind { Stroke, Circle } kind;
        int index = -1;
        QPolygon poly;
        QRect rect;
    };
    QVector<EraseOp> m_eraseHistory;
    QVector<EraseOp> m_eraseRedo;

    bool m_lastCanUndo = false;
    bool m_lastCanRedo = false;

    void notifyState();
    void eraseAt(const QPoint &pt);
};

#endif // RENDERAREA_H
