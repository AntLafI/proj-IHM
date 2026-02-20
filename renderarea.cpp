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

void RenderArea::paintEvent(QPaintEvent *event){
    painter.begin(this);

    if (!m_background.isNull())
        painter.drawImage(rect(), m_background);

    painter.setPen(pen);

    for (const QPolygon &poly : m_strokes)
        painter.drawPoints(poly);

    if (!m_currentStroke.isEmpty())
        painter.drawPoints(m_currentStroke);

    painter.end();
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
