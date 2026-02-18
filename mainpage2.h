#ifndef MAINPAGE2_H
#define MAINPAGE2_H

#include <QMainWindow>

namespace Ui {
class mainPage2;
}

class mainPage2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit mainPage2(QWidget *parent = nullptr);
    ~mainPage2();

private:
    Ui::mainPage2 *ui;
};

#endif // MAINPAGE2_H
