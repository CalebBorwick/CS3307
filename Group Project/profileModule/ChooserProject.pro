QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = ChooserProject
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS
CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    guestwindow.cpp \
    main.cpp \
    main_window.cpp \
    userwindow.cpp

HEADERS += \
    guestwindow.h \
    main_window.h \
    userwindow.h

FORMS += \
    guestwindow.ui \
    mainwindow.ui \
    userwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
