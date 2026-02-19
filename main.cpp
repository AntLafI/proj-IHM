#include "mainwindow.h"

#include <QApplication>
#include "Theme/AppStyle.h"
int main(int argc, char *argv[])
{
    AppStyle *appS = new AppStyle();
    QApplication a(argc, argv);
    a.setStyle(appS);
    MainWindow w;
    w.show();
    return a.exec();
}
