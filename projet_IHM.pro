QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    imageviewer.cpp \
    main.cpp \
    Theme/AppStyle.cpp \
    Theme/Theme.cpp \
    mainwindow.cpp

HEADERS += \
    Theme/PaletteThemeMapper.h \
    Theme/StyleHelpers/CompisiteElem/MenuDrawer.h \
    Theme/StyleHelpers/PrimitiveElem/CheckboxDrawer.h \
    mainwindow.h \
    Theme/Theme.h \
    Theme/AppStyle.h \
    imageviewer.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
