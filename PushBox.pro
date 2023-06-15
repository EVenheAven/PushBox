QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    choosescene.cpp \
    ex_scene.cpp \
    gamedata.cpp \
    kirby.cpp \
    main.cpp \
    mainwindow.cpp \
    mypushbutton.cpp \
    obstacle.cpp \
    playscene.cpp \
    rule.cpp

HEADERS += \
    choosescene.h \
    config.h \
    ex_scene.h \
    gamedata.h \
    kirby.h \
    mainwindow.h \
    mypushbutton.h \
    obstacle.h \
    playscene.h \
    rule.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
QT += sql
QT += multimedia

##LIBS += "D:\mysql\mysql-8.0.33-winx64\mysql-8.0.33-winx64\lib\libmysql.dll"

#INCLUDEPATH += "D:\mysql\mysql-8.0.33-winx64\mysql-8.0.33-winx64\include"

#DEPENDPATH += "D:\mysql\mysql-8.0.33-winx64\mysql-8.0.33-winx64\include"

#DESTDIR = ../mysql/myLib/
