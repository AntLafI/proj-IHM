#include "renderarea.h"

#include <QColor>
#include <QPalette>
#include <QPolygon>

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

    m_baseSize = QSize(); // pas encore fixé
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
    return !m_strokes.isEmpty() || !m_currentStroke.isEmpty();
}

bool RenderArea::canRedo() const{
    return !m_redoStrokes.isEmpty();
}

void RenderArea::undo(){
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
    }
}

void RenderArea::redo(){
    if (!m_redoStrokes.isEmpty()) {
        m_strokes.append(m_redoStrokes.takeLast());
        update();
        notifyState();
        emit modified();
    }
}

void RenderArea::mousePressEvent(QMouseEvent *event){
    if (m_baseSize.isEmpty())
        m_baseSize = this->size(); // fixe la taille de référence au premier tracé

    m_currentStroke.clear();
    m_currentStroke << event->pos();
    update();
    notifyState();
}

void RenderArea::mouseMoveEvent(QMouseEvent *event){
    m_currentStroke << event->pos();
    update();
    notifyState();
}

void RenderArea::mouseReleaseEvent(QMouseEvent *event){
    if (!m_currentStroke.isEmpty()) {
        m_currentStroke << event->pos();
        m_strokes.append(m_currentStroke);
        m_currentStroke.clear();
        m_redoStrokes.clear();
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

    // Fond : s’adapte toujours à la cible
    if (!m_background.isNull())
        p->drawImage(QRect(QPoint(0,0), targetSize), m_background);

    // Si pas encore de baseSize (pas de tracé), utiliser la taille cible
    const int bw = m_baseSize.width()  > 0 ? m_baseSize.width()  : tw;
    const int bh = m_baseSize.height() > 0 ? m_baseSize.height() : th;

    const qreal sx = static_cast<qreal>(tw) / static_cast<qreal>(bw);
    const qreal sy = static_cast<qreal>(th) / static_cast<qreal>(bh);

    p->save();
    p->setRenderHint(QPainter::Antialiasing, true);
    p->scale(sx, sy);

    p->setPen(pen);

    for (const QPolygon &poly : m_strokes)
        p->drawPoints(poly);

    if (!m_currentStroke.isEmpty())
        p->drawPoints(m_currentStroke);

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
