#include "mainpage.h"
#include "ui_mainpage.h"
#include "renderarea.h"

mainPage::mainPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::mainPage)
{
    ui->setupUi(this);


    RenderArea *page = new RenderArea (this) ;
    mainPage *pageToolBar = new mainPage(this) ;

    ui-> verticalLayout_2 -> addWidget(pageToolBar) ;
    //ui -> verticalLayout_2 -> addWidget(page) ;
}

mainPage::~mainPage()
{
    delete ui;
}
