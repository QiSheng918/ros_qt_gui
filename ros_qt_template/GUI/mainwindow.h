#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gui_myrviz.h"
#include "qcustomplot.h"
#include "data_plot.h"
#include <QProcess>
#include <QDebug>
#include <QString>
#include <QTimer>


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
    void readSerial();
    void refresh();
    void ReadOutput();
//private Q_SLOTS:


private:
    Ui::MainWindow *ui;
    MyViz *viz;
    data_plot *Data_plot;
    QProcess *terminal;
    QProcess *ros_terminal;
    QTimer *timer;
};

#endif // MAINWINDOW_H
