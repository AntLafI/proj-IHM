#include "imageviewer.h"
#include <QWheelEvent>
#include <QPixmap>

ImageViewer::ImageViewer(QWidget *parent)
    : QGraphicsView(parent),
    m_scene(new QGraphicsScene(this)),
    m_item(new QGraphicsPixmapItem)
{
    setScene(m_scene);
    m_scene->addItem(m_item);

    setRenderHints(QPainter::Antialiasing |
                   QPainter::SmoothPixmapTransform);

    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    setResizeAnchor(QGraphicsView::AnchorUnderMouse);
}

bool ImageViewer::loadImage(const QString &fileName)
{
    QPixmap pixmap(fileName);
    if (pixmap.isNull())
        return false;

    m_item->setPixmap(pixmap);
    m_scene->setSceneRect(pixmap.rect());
    fitInView(m_item, Qt::KeepAspectRatio);
    return true;
}

QPixmap ImageViewer::currentPixmap() const
{
    if (!m_item || m_item->pixmap().isNull())
        return QPixmap();

    return m_item->pixmap();
}

void ImageViewer::wheelEvent(QWheelEvent *event)
{
    constexpr double factor = 1.15;
    if (event->angleDelta().y() > 0)
        scale(factor, factor);
    else
        scale(1.0 / factor, 1.0 / factor);
}
