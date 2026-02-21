#ifndef SCROLLBAR_H
#define SCROLLBAR_H

#include <QWidget>

namespace Ui {
class ScrollBar;
}

class ScrollBar : public QWidget
{
    Q_OBJECT

public:
    explicit ScrollBar(QWidget *parent = nullptr);
    ~ScrollBar();

signals:
    void circleToolClicked();
    void rectToolClicked();
    void eraserToolClicked();

private:
    Ui::ScrollBar *ui;
};

#endif // SCROLLBAR_H
