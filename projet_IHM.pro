QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT       += svg

CONFIG += c++17

SOURCES += \
    imageviewer.cpp \
    main.cpp \
    mainwindow.cpp \
    renderarea.cpp \
    scrollbar.cpp

HEADERS += \
    imageviewer.h \
    mainwindow.h \
    renderarea.h \
    scrollbar.h

FORMS += \
    mainwindow.ui \
    renderarea.ui \
    scrollbar.ui

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc

DISTFILES += \
    ../Images/1266212.svg \
    ../Images/calque.png \
    ../Images/carre.png \
    ../Images/circle.png \
    ../Images/gomme.png \
    ../Images/palette.png \
    ../Images/selector_tool.png \
    ../Images/tletter.png \
    ../Images/unzoom.png \
    ../Images/zoom_tool.png
