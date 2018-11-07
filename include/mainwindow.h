 #ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include <QProcess>
#include <QDebug>
#include <QString>
#include <QTimer>
#include <QMouseEvent>
#include <QDir>
#include <QMessageBox>
#include "mymessagebox.h"
#include "gui_myrviz.h"
#include "qcustomplot.h"
#include "data_plot.h"
#include "ros_service_pub.h"
#include "ui_mainwindow.h"
#include <QTime>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void StopPtn_clicked();
    void StartPtn_clicked();
    void QuitPtn_clicked();
    void PythonPth_clicked();
    void update();
    void ReadOutput();
    void readOutput();
    void textBrower_textChanged();
    void Ptn_clicked();
    void RqtPtn_clicked();

private:
    Ui::MainWindow *ui;
    MyViz *viz;
    data_plot *DataPlot;
//    QProcess *bluetooth_terminal;
    QTimer *UpdateTimer;
    bool RobotModelFlag;

    QTime initTime,tempTime;


    ros_service_pub *ServicePub;
    QProcess *ros_terminal;
    QProcess *python_terminal;
    QProcess *rqt_terminal;
    QDir *BluetoothDir;
    MyMessageBox *messageBox;

    QString SerialNumber;

    void mouseDoubleClickEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
};

#endif // MAINWINDOW_H
