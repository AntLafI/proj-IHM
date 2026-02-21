#ifndef RENDERAREA_H
#define RENDERAREA_H

#include "ui_renderarea.h"
#include <QWidget>
#include <QMouseEvent>
#include <QPen>
#include <QPainter>
#include <QImage>
#include <QPolygon>
#include <QVector>
#include <QSize>
#include <QRect>
#include <QFont>
#include <QString>

class RenderArea : public QWidget, private Ui::RenderArea
{
    Q_OBJECT

public:
    enum Tool { Freehand, Circle, Rect, Text, Eraser };

    explicit RenderArea(QWidget *parent = nullptr);

    void setBackgroundImage(const QImage &img);
    void clearBackground();
    bool canUndo() const;
    bool canRedo() const;
    void renderToPainter(QPainter *p, const QSize &size) const;
    void setTool(Tool t){ m_tool = t; }

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

    QImage m_background;

    QPolygon m_currentStroke;
    QVector<QPolygon> m_strokes;
    QVector<QPolygon> m_redoStrokes;

    QRect m_currentCircle;
    QVector<QRect> m_circles;
    QVector<QRect> m_redoCircles;

    QRect m_currentRect;
    QVector<QRect> m_rects;
    QVector<QRect> m_redoRects;

    struct TextItem {
        QPoint pos;
        QString text;
        QFont font;
        QColor color;
    };
    QVector<TextItem> m_texts;
    QVector<TextItem> m_redoTexts;

    Tool m_tool = Freehand;

    QSize m_baseSize;

    QPoint m_pressPos;

    struct EraseOp {
        enum Kind { Stroke, Circle, Rect, Text } kind;
        int index = -1;
        QPolygon poly;
        QRect rect;
        TextItem txt;
    };
    QVector<EraseOp> m_eraseHistory;
    QVector<EraseOp> m_eraseRedo;

    bool m_lastCanUndo = false;
    bool m_lastCanRedo = false;

    void notifyState();
    void eraseAt(const QPoint &pt);
};

#endif // RENDERAREA_H
