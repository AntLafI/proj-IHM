#include "scrollbar.h"
#include "ui_scrollbar.h"

#include <QPushButton>
#include <QPixmap>

#include <QScrollArea>
#include <QVBoxLayout>


ScrollBar::ScrollBar(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ScrollBar)
{
    ui->setupUi(this);

    QVBoxLayout *selfLayout = new QVBoxLayout(this);

    QScrollArea *scrollArea = new QScrollArea() ;
    QWidget *container = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(container);

    scrollArea->setBackgroundRole(QPalette::Dark);

    QStringList logo = {":/new/icons/images/1266212.svg",
                        ":/new/icons/images/calque.png",
                        ":/new/icons/images/carre.png",
                        ":/new/icons/images/circle.png",
                        ":/new/icons/images/gomme.png",
                        ":/new/icons/images/palette.png",
                        ":/new/icons/images/selector_tool.png",
                        ":/new/icons/images/tletter.png",
                        ":/new/icons/images/unzoom.png",
                        ":/new/icons/images/zoom_tool.png"} ;


    for(const QString &path : logo) {
        QPushButton *button = new QPushButton(this);

        button-> setIcon((QIcon(path))) ;
        button->setIconSize(QSize(50, 50));
        button->setFixedSize(60, 60);

        layout->addWidget(button);

    }

    scrollArea->setWidget(container);
    scrollArea->setWidgetResizable(true);
    scrollArea->setBackgroundRole(QPalette::Dark);

    selfLayout->addWidget(scrollArea);

}

ScrollBar::~ScrollBar()
{
    delete ui;
}
