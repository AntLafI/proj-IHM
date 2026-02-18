#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QScrollArea>
#include <QHBoxLayout>
#include "renderarea.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QWidget *toolWidget = ui->widget;

    toolWidget->setFixedWidth(80);
    toolWidget->setMinimumHeight(900);
    //je peux changer la taille si necessaire

    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setWidget(toolWidget);
    scrollArea->setWidgetResizable(false);

    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);


    scrollArea->setFixedWidth(95);


    RenderArea *renderArea = new RenderArea;

    QHBoxLayout *mainLayout = new QHBoxLayout(ui->centralwidget);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0,0,0,0);


    mainLayout->addWidget(scrollArea);
    mainLayout->addWidget(renderArea);
}

MainWindow::~MainWindow()
{
    delete ui;
}
