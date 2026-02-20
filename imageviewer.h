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
    bool setPixmap(const QPixmap &pm);
    QPixmap currentPixmap() const;

protected:
    void wheelEvent(QWheelEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    QGraphicsScene *m_scene;
    QGraphicsPixmapItem *m_item;
    bool m_hasPixmap = false;
};

#endif // IMAGEVIEWER_H
