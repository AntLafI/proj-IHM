#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QGraphicsView>
#include <QGraphicsPixmapItem>

class ImageViewer : public QGraphicsView
{
    Q_OBJECT

public:
    explicit ImageViewer(QWidget *parent = nullptr);

    bool loadImage(const QString &fileName);
    QPixmap currentPixmap() const;

protected:
    void wheelEvent(QWheelEvent *event) override;

private:
    QGraphicsScene *m_scene;
    QGraphicsPixmapItem *m_item;
};

#endif // IMAGEVIEWER_H
