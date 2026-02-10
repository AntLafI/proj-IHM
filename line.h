#ifndef LINE_H
#define LINE_H

#include <QObject>
#include <QColor>
#include <QPoint>

class Line : public QObject
{
    Q_OBJECT
public:
    explicit Line(QObject *parent = nullptr);
    Line(const Line& line){
        width = line.getWidth();
        color = line.getColor();
        points = line.getPoints();
    }
    ~Line(){
    };

    Line&
    operator=(const Line& line){
        width = line.getWidth();
        color = line.getColor();
        points = line.getPoints();
        return *this;
    }

    QList<QPoint> getPoints() const {return points;};
    void addPoint(QPoint point){points.append(point);};
    void setWidth(int w){width = w;}
    void setColor(QColor col){color = col;}
    QColor getColor() const {return color;}
    int getWidth() const {return width;}

private:
    int width = 1;
    QColor color;
    QList<QPoint> points;
signals:
};

#endif // LINE_H
