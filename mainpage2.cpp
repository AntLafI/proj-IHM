#include "mainpage.h"
#include "ui_mainpage.h"
#include "renderarea.h"

#include <QWidget>
#include <QVBoxLayout>

mainPage::mainPageQWidget *parent)
    : QWidget(parent)
    , ui(new Ui::mainPage)
{
    ui->setupUi(this);

    QHBoxLayout *mainLayout = ui->horizontalLayout;

    QWidget *leftContainer = new QWidget();
    QVBoxLayout *leftLayout = new QVBoxLayout(leftContainer);

    mainPage *pageToolBar = new mainPage(this) ;

    leftLayout->addWidget(pageToolBar);


    RenderArea *renderArea = new RenderArea(this);

    mainLayout->addWidget(leftContainer); // Index 0
    mainLayout->addWidget(renderArea);    // Index 1

    mainLayout->setStretch(0, 3);
    mainLayout->setStretch(1, 7);


}

mainPage::~mainPage()
{
    delete ui;
}
