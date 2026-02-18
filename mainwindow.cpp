#include "mainwindow.h"

#include <QPushButton>
#include <QPixmap>

#include <QScrollArea>

#include <QWidget>
#include <QVBoxLayout>
#include <QMainWindow>

#include "scrollbar.h"
#include "renderarea.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QHBoxLayout *mainLayout = ui->horizontalLayout;

    ScrollBar *myScrollBar = new ScrollBar(this);
    RenderArea *myRenderArea = new RenderArea(this);

    mainLayout->addWidget(myScrollBar); // Index 0
    mainLayout->addWidget(myRenderArea);  // Index 1

    mainLayout->setStretch(0, 3);
    mainLayout->setStretch(1, 7);


}

MainWindow::~MainWindow(){ ;
    delete ui ;
}
