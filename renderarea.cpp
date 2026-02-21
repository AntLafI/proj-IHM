#include "renderarea.h"

#include <QColor>
#include <QPalette>
#include <QPolygon>
#include <QtMath>

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

    m_baseSize = QSize();
    notifyState();
}

void RenderArea::setBackgroundImage(const QImage &img){
    m_background = img;
    update();
}

void RenderArea::clearBackground(){
    m_background = QImage();
    update();
}

bool RenderArea::canUndo() const{
    return !m_strokes.isEmpty() || !m_currentStroke.isEmpty()
    || !m_circles.isEmpty() || !m_currentCircle.isNull()
        || !m_eraseHistory.isEmpty();
}

bool RenderArea::canRedo() const{
    return !m_redoStrokes.isEmpty() || !m_redoCircles.isEmpty() || !m_eraseRedo.isEmpty();
}

void RenderArea::undo(){
    if (!m_eraseHistory.isEmpty()) {
        EraseOp op = m_eraseHistory.takeLast();
        if (op.kind == EraseOp::Stroke) {
            int ins = qBound(0, op.index, m_strokes.size());
            m_strokes.insert(ins, op.poly);
        } else {
            int ins = qBound(0, op.index, m_circles.size());
            m_circles.insert(ins, op.rect);
        }
        m_eraseRedo.append(op);
        update();
        notifyState();
        emit modified();
        return;
    }

    if (!m_currentStroke.isEmpty()) {
        m_redoStrokes.append(m_currentStroke);
        m_currentStroke.clear();
        update();
        notifyState();
        emit modified();
        return;
    }
    if (!m_strokes.isEmpty()) {
        m_redoStrokes.append(m_strokes.takeLast());
        update();
        notifyState();
        emit modified();
        return;
    }
    if (!m_currentCircle.isNull()) {
        m_redoCircles.append(m_currentCircle);
        m_currentCircle = QRect();
        update();
        notifyState();
        emit modified();
        return;
    }
    if (!m_circles.isEmpty()) {
        m_redoCircles.append(m_circles.takeLast());
        update();
        notifyState();
        emit modified();
    }
}

void RenderArea::redo(){
    if (!m_eraseRedo.isEmpty()) {
        EraseOp op = m_eraseRedo.takeLast();
        if (op.kind == EraseOp::Stroke) {
            if (op.index >= 0 && op.index < m_strokes.size())
                m_strokes.remove(op.index);
            else {
                for (int i = m_strokes.size()-1; i >= 0; --i) {
                    if (m_strokes[i] == op.poly) { m_strokes.remove(i); break; }
                }
            }
        } else {
            if (op.index >= 0 && op.index < m_circles.size())
                m_circles.remove(op.index);
            else {
                for (int i = m_circles.size()-1; i >= 0; --i) {
                    if (m_circles[i] == op.rect) { m_circles.remove(i); break; }
                }
            }
        }
        m_eraseHistory.append(op);
        update();
        notifyState();
        emit modified();
        return;
    }

    if (!m_redoStrokes.isEmpty()) {
        m_strokes.append(m_redoStrokes.takeLast());
        update();
        notifyState();
        emit modified();
        return;
    }
    if (!m_redoCircles.isEmpty()) {
        m_circles.append(m_redoCircles.takeLast());
        update();
        notifyState();
        emit modified();
    }
}

void RenderArea::setTool(Tool t){
    m_tool = t;
}

void RenderArea::mousePressEvent(QMouseEvent *event){
    if (m_baseSize.isEmpty())
        m_baseSize = this->size();

    if (m_tool == Freehand) {
        m_currentStroke.clear();
        m_currentStroke << event->pos();
    } else if (m_tool == Circle) {
        m_pressPos = event->pos();
        m_currentCircle = QRect();
    } else {
        eraseAt(event->pos());
    }
    update();
    notifyState();
}

void RenderArea::mouseMoveEvent(QMouseEvent *event){
    if (m_tool == Freehand) {
        m_currentStroke << event->pos();
    } else if (m_tool == Circle) {
        const QPoint p0 = m_pressPos;
        const QPoint p1 = event->pos();
        int dx = p1.x() - p0.x();
        int dy = p1.y() - p0.y();
        int side = qMin(qAbs(dx), qAbs(dy));
        int rx = dx >= 0 ? side : -side;
        int ry = dy >= 0 ? side : -side;
        QRect r(p0, p0 + QPoint(rx, ry));
        m_currentCircle = r.normalized();
    } else {
        eraseAt(event->pos());
    }
    update();
    notifyState();
}

void RenderArea::mouseReleaseEvent(QMouseEvent *event){
    if (m_tool == Freehand) {
        if (!m_currentStroke.isEmpty()) {
            m_currentStroke << event->pos();
            m_strokes.append(m_currentStroke);
            m_currentStroke.clear();
            m_redoStrokes.clear();
            m_eraseRedo.clear();
            update();
            notifyState();
            emit modified();
        }
    } else if (m_tool == Circle) {
        if (!m_currentCircle.isNull()) {
            m_circles.append(m_currentCircle);
            m_currentCircle = QRect();
            m_redoCircles.clear();
            m_eraseRedo.clear();
            update();
            notifyState();
            emit modified();
        }
    } else {
        eraseAt(event->pos());
        update();
        notifyState();
        emit modified();
    }
}

void RenderArea::paintEvent(QPaintEvent *){
    painter.begin(this);
    renderToPainter(&painter, size());
    painter.end();
}

void RenderArea::renderToPainter(QPainter *p, const QSize &targetSize) const{
    const int tw = qMax(1, targetSize.width());
    const int th = qMax(1, targetSize.height());

    if (!m_background.isNull())
        p->drawImage(QRect(QPoint(0,0), targetSize), m_background);

    const int bw = m_baseSize.width()  > 0 ? m_baseSize.width()  : tw;
    const int bh = m_baseSize.height() > 0 ? m_baseSize.height() : th;

    const qreal sx = static_cast<qreal>(tw) / static_cast<qreal>(bw);
    const qreal sy = static_cast<qreal>(th) / static_cast<qreal>(bh);

    p->save();
    p->setRenderHint(QPainter::Antialiasing, true);
    p->scale(sx, sy);

    p->setPen(pen);
    p->setBrush(Qt::NoBrush);

    for (const QPolygon &poly : m_strokes)
        p->drawPoints(poly);

    if (!m_currentStroke.isEmpty())
        p->drawPoints(m_currentStroke);

    for (const QRect &rc : m_circles)
        p->drawEllipse(rc);

    if (!m_currentCircle.isNull())
        p->drawEllipse(m_currentCircle);

    p->restore();
}

void RenderArea::notifyState(){
    bool cu = canUndo();
    bool cr = canRedo();
    if (cu != m_lastCanUndo) {
        m_lastCanUndo = cu;
        emit canUndoChanged(cu);
    }
    if (cr != m_lastCanRedo) {
        m_lastCanRedo = cr;
        emit canRedoChanged(cr);
    }
}

void RenderArea::eraseAt(const QPoint &pt){
    const QSize cur = this->size();
    const int tw = qMax(1, cur.width());
    const int th = qMax(1, cur.height());
    const int bw = m_baseSize.width()  > 0 ? m_baseSize.width()  : tw;
    const int bh = m_baseSize.height() > 0 ? m_baseSize.height() : th;
    const qreal sx = static_cast<qreal>(tw) / static_cast<qreal>(bw);
    const qreal sy = static_cast<qreal>(th) / static_cast<qreal>(bh);
    const QPointF basePtF(pt.x() / sx, pt.y() / sy);
    const QPoint basePt(qRound(basePtF.x()), qRound(basePtF.y()));

    for (int i = m_circles.size() - 1; i >= 0; --i) {
        if (m_circles[i].contains(basePt)) {
            EraseOp op;
            op.kind = EraseOp::Circle;
            op.index = i;
            op.rect = m_circles[i];
            m_circles.remove(i);
            m_eraseHistory.append(op);
            m_redoCircles.clear();
            m_redoStrokes.clear();
            m_eraseRedo.clear();
            emit modified();
            return;
        }
    }

    const int radius = 6;
    for (int i = m_strokes.size() - 1; i >= 0; --i) {
        const QPolygon &poly = m_strokes[i];
        for (const QPoint &p : poly) {
            if (qAbs(p.x() - basePt.x()) <= radius && qAbs(p.y() - basePt.y()) <= radius) {
                EraseOp op;
                op.kind = EraseOp::Stroke;
                op.index = i;
                op.poly = poly;
                m_strokes.remove(i);
                m_eraseHistory.append(op);
                m_redoCircles.clear();
                m_redoStrokes.clear();
                m_eraseRedo.clear();
                emit modified();
                return;
            }
        }
    }
}
