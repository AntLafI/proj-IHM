QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainpage.cpp \
    mainwindow.cpp \
    renderarea.cpp

HEADERS += \
    mainpage.h \
    mainwindow.h \
    renderarea.h

FORMS += \
    mainpage.ui \
    mainwindow.ui \
    renderarea.ui

# Default rules for deployment.
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
