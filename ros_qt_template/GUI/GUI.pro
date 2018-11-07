#-------------------------------------------------
#
# Project created by QtCreator 2017-09-02T01:56:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets  printsupport serialport


TARGET = GUI
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
           mainwindow.cpp\
           gui_myrviz.cpp\
           sub_node.cpp\
           qcustomplot.cpp\
           data_plot.cpp

HEADERS  += mainwindow.h\
            guimyrviz.h\
            sub_node.h\
            qcustomplot.h\
            data_plot.h

FORMS    += mainwindow.ui


INCLUDEPATH += -I /opt/ros/kinetic/include

DEPENDPATH +=  /opt/ros/kinetic/include


unix:!macx: LIBS += -L /opt/ros/kinetic/lib/ -lroscpp
unix:!macx: LIBS += -L /opt/ros/kinetic/lib/ -lroslib
unix:!macx: LIBS += -L /opt/ros/kinetic/lib/ -lpthread
unix:!macx: LIBS += -L /opt/ros/kinetic/lib/ -lroscpp_serialization
unix:!macx: LIBS += -L /opt/ros/kinetic/lib/ -lrostime
unix:!macx: LIBS += -L /opt/ros/kinetic/lib/ -lrosconsole
unix:!macx: LIBS += -L /opt/ros/kinetic/lib/ -lrosconsole_log4cxx
unix:!macx: LIBS += -L /opt/ros/kinetic/lib/ -lrosconsole_backend_interface
unix:!macx: LIBS += -L /opt/ros/kinetic/lib/ -lxmlrpcpp
