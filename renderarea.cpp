#include "renderarea.h"

#include <QColor>
#include <QPalette>
#include <QBrush>
#include <QPainter>
#include <QPolygonF>
#include <QPainterPath>

RenderArea::RenderArea(QWidget *parent)
    : QGraphicsView(parent)
{
    setupUi(this);
    setScene(new QGraphicsScene(this));
    setAlignment(Qt::AlignCenter);

    QColor col; col.setRgb(255,255,255);
    QPalette pal; setAutoFillBackground(true);
    pal.setColor(QPalette::Window, col);
    setPalette(pal);

    currentPen.setStyle(Qt::SolidLine);
    currentPen.setColor(QColor(255,0,0));
    currentPen.setWidth(5);

    setRenderHint(QPainter::Antialiasing, true);
    notifyState();
}

void RenderArea::setBackgroundImage(const QImage &img){
    if (img.isNull()) return;
    if (!m_bgItem) {
        m_bgItem = new QGraphicsPixmapItem();
        m_bgItem->setZValue(-1000.0);
        scene()->addItem(m_bgItem);
    }
    m_bgItem->setPixmap(QPixmap::fromImage(img));
    scene()->setSceneRect(m_bgItem->boundingRect());
}

void RenderArea::clearBackground(){
    if (m_bgItem) {
        scene()->removeItem(m_bgItem);
        delete m_bgItem;
        m_bgItem = nullptr;
    }
}

bool RenderArea::canUndo() const{
    return !m_undo.isEmpty();
}

bool RenderArea::canRedo() const{
    return !m_redo.isEmpty();
}

void RenderArea::setTool(Tool t){
    m_tool = t;
}

void RenderArea::pushAdd(QGraphicsItem *it){
    m_undo.append(Op{Op::AddItem, it});
    m_redo.clear();
    notifyState();
    emit modified();
}

void RenderArea::pushRemove(QGraphicsItem *it){
    m_undo.append(Op{Op::RemoveItem, it});
    m_redo.clear();
    notifyState();
    emit modified();
}

void RenderArea::undo(){
    if (m_undo.isEmpty()) return;
    Op op = m_undo.takeLast();
    if (op.kind == Op::AddItem) {
        if (op.item && op.item->scene())
            op.item->scene()->removeItem(op.item);
        m_redo.append(op);
    } else {
        if (op.item && !op.item->scene())
            scene()->addItem(op.item);
        m_redo.append(op);
    }
    notifyState();
    emit modified();
}

void RenderArea::redo(){
    if (m_redo.isEmpty()) return;
    Op op = m_redo.takeLast();
    if (op.kind == Op::AddItem) {
        if (op.item && !op.item->scene())
            scene()->addItem(op.item);
        m_undo.append(op);
    } else {
        if (op.item && op.item->scene())
            op.item->scene()->removeItem(op.item);
        m_undo.append(op);
    }
    notifyState();
    emit modified();
}

void RenderArea::mousePressEvent(QMouseEvent *event){
    const QPointF spt = mapToScene(event->pos());

    if (event->button() == Qt::RightButton) {
        m_tool = Eraser;
    }

    if (m_tool == Freehand) {
        m_currentPolyPts.clear();
        m_currentPolyPts.append(spt);
        if (!m_currentPoly) {
            m_currentPoly = new QGraphicsPolygonItem();
            m_currentPoly->setPen(currentPen);
            m_currentPoly->setBrush(Qt::NoBrush);
            scene()->addItem(m_currentPoly);
        }
        m_currentPoly->setPolygon(QPolygonF(m_currentPolyPts));
    } else if (m_tool == Circle) {
        m_pressScene = spt;
        if (!m_currentEllipse) {
            m_currentEllipse = new QGraphicsEllipseItem();
            m_currentEllipse->setPen(currentPen);
            m_currentEllipse->setBrush(Qt::NoBrush);
            scene()->addItem(m_currentEllipse);
        }
        QRectF r(m_pressScene, m_pressScene);
        m_currentEllipse->setRect(r.normalized());
    } else if (m_tool == Rect) {
        m_pressScene = spt;
        if (!m_currentRect) {
            m_currentRect = new QGraphicsRectItem();
            m_currentRect->setPen(currentPen);
            m_currentRect->setBrush(Qt::NoBrush);
            scene()->addItem(m_currentRect);
        }
        QRectF r(m_pressScene, m_pressScene);
        m_currentRect->setRect(r.normalized());
    } else {
        eraseAt(event->pos());
    }

    QGraphicsView::mousePressEvent(event);
}

void RenderArea::mouseMoveEvent(QMouseEvent *event){
    const QPointF spt = mapToScene(event->pos());

    if (m_tool == Freehand) {
        if (m_currentPoly) {
            m_currentPolyPts.append(spt);
            m_currentPoly->setPolygon(QPolygonF(m_currentPolyPts));
        }
    } else if (m_tool == Circle) {
        if (m_currentEllipse) {
            const QPointF p0 = m_pressScene;
            const QPointF p1 = spt;
            const qreal dx = p1.x() - p0.x();
            const qreal dy = p1.y() - p0.y();
            const qreal side = qMin(qAbs(dx), qAbs(dy));
            const qreal rx = dx >= 0 ? side : -side;
            const qreal ry = dy >= 0 ? side : -side;
            QRectF r(p0, QPointF(p0.x()+rx, p0.y()+ry));
            m_currentEllipse->setRect(r.normalized());
        }
    } else if (m_tool == Rect) {
        if (m_currentRect) {
            QRectF r(m_pressScene, spt);
            m_currentRect->setRect(r.normalized());
        }
    } else {
        eraseAt(event->pos());
    }

    QGraphicsView::mouseMoveEvent(event);
}

void RenderArea::mouseReleaseEvent(QMouseEvent *event){
    if (m_tool == Freehand) {
        if (m_currentPoly) {
            pushAdd(m_currentPoly);
            m_currentPoly = nullptr;
            m_currentPolyPts.clear();
        }
    } else if (m_tool == Circle) {
        if (m_currentEllipse) {
            pushAdd(m_currentEllipse);
            m_currentEllipse = nullptr;
        }
    } else if (m_tool == Rect) {
        if (m_currentRect) {
            pushAdd(m_currentRect);
            m_currentRect = nullptr;
        }
    } else {
        eraseAt(event->pos());
    }

    QGraphicsView::mouseReleaseEvent(event);
}

void RenderArea::eraseAt(const QPoint &viewPos){
    const QPointF spt = mapToScene(viewPos);
    const qreal r = 8.0;
    QPainterPath area;
    area.addEllipse(QRectF(spt.x() - r, spt.y() - r, 2*r, 2*r));

    QList<QGraphicsItem*> hits = scene()->items(area,
                                                 Qt::IntersectsItemShape,
                                                 Qt::DescendingOrder,
                                                 transform());

    for (QGraphicsItem *it : hits) {
        if (!it) continue;
        if (it == m_bgItem) continue;
        if (it == m_currentPoly || it == m_currentEllipse || it == m_currentRect) continue;

        if (it->scene())
            it->scene()->removeItem(it);
        pushRemove(it);
        break;
    }
}

void RenderArea::renderToPainter(QPainter *p, const QSize &size) const{
    QRectF target(QPointF(0,0), QSizeF(size));
    scene()->render(p, target, scene()->sceneRect(), Qt::KeepAspectRatio);
}

void RenderArea::notifyState(){
    emit canUndoChanged(canUndo());
    emit canRedoChanged(canRedo());
}
