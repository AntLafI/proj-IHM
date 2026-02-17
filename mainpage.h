#ifndef MAINPAGE_H
#define MAINPAGE_H
#include "ui_mainpage.h"
#include <QWidget>

namespace Ui {
class mainPage;
}

class mainPage : public QWidget
{
    Q_OBJECT

public:
    explicit mainPage(QWidget *parent = nullptr);
    ~mainPage();

private:
    Ui::mainPage *ui;
};

#endif // MAINPAGE_H
