#ifndef RENDERAREA_H
#define RENDERAREA_H

#include "ui_renderarea.h"
#include <QMouseEvent>
#include <QPen>
#include <QPainter>
#include <QImage>
#include <QPolygon>
#include <QVector>

class RenderArea : public QWidget, private Ui::RenderArea
{
    Q_OBJECT

public:
    explicit RenderArea(QWidget *parent = nullptr);

    void setBackgroundImage(const QImage &img);
    void clearBackground();
    bool canUndo() const;
    bool canRedo() const;

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

    bool m_lastCanUndo = false;
    bool m_lastCanRedo = false;

    void notifyState();
};

#endif // RENDERAREA_H
