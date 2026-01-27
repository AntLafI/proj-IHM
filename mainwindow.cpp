#include "mainwindow.h"

#include "renderarea.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);
    RenderArea *ra = new RenderArea();
    this->setCentralWidget(ra);
}

MainWindow::~MainWindow() {}
