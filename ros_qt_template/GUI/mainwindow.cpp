#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "stdio.h"
#include <QStringList>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("ros_qt_template");

     viz=new MyViz();
     ui->VizArea->addSubWindow(viz, Qt::FramelessWindowHint); // FramelessWindowHint removes close, minimize and maximize title bar
     viz->showMaximized();
//     viz->subscribeTopics("joint_states");
 //    int i=system("gnome-terminal -x bash -c \"source /opt/ros/kinetic/setup.bash; roslaunch urdf_tutorial display.launch model:='/opt/ros/kinetic/share/urdf_tutorial/urdf/06-flexible.urdf'\" &");
//    p=ui->qcustomplotWidget;
//    begin_plot();
    Data_plot=new data_plot(ui->qcustomplotWidget);
    terminal=new QProcess;
    terminal->setWorkingDirectory("/dev/serial/by-path/");
    terminal->start("ls");
    connect(terminal,SIGNAL(readyRead()),this,SLOT(readSerial()));
//    QString run_cmd = QString("roslaunch ")
//          + QString("urdf_tutorial") + QString(" ")
//          + QString("mydisplay.launch");
//       int n = run_cmd.length()+1;
//      char cmd[n];
//      std::string dome2 = run_cmd.toStdString();
//      strncpy(cmd, dome2.c_str(), n-1);
//      cmd[n-1] =0;
//      qDebug()<<cmd;
//     int m = system(cmd);
       ros_terminal=new QProcess;
       if(ros_terminal)  ros_terminal->close();
       timer=new QTimer();
       connect(timer,SIGNAL(timeout()),this,SLOT(refresh()));
       timer->start(10);
       connect(ui->StartButton,SIGNAL(clicked()),this,SLOT(StartPtn_clicked()));
       connect(ui->StopButton,SIGNAL(clicked()),this,SLOT(StopPtn_clicked()));
       connect(ui->QuitButton,SIGNAL(clicked()),this,SLOT(QuitPtn_clicked()));
       connect(ros_terminal,SIGNAL(readyRead()),this,SLOT(ReadOutput()));

}

MainWindow::~MainWindow()
{
    delete ui;
    delete viz;
    delete Data_plot;
    delete terminal;
    if(!ros_terminal)  delete ros_terminal;
    else {
      ros_terminal->close();
      delete ros_terminal;
    }
    delete timer;
}



void MainWindow::StartPtn_clicked()
{
    // int i=system("gnome-terminal -x bash -c \"source /opt/ros/kinetic/setup.bash; roslaunch urdf_tutorial display.launch model:='/opt/ros/kinetic/share/urdf_tutorial/urdf/06-flexible.urdf'\" ");
    QString run_cmd = QString("roslaunch ")
        + QString("urdf_tutorial") + QString(" ")
        + QString("myrobot_display.launch");
    int n = run_cmd.length()+1;
    char cmd[n];
    std::string cmd_string = run_cmd.toStdString();
    strncpy(cmd,cmd_string.c_str(),n-1);
    cmd[n-1] =0;
    qDebug()<<cmd;
//   int m = system(cmd);
    ros_terminal->start(cmd);
}

void MainWindow::StopPtn_clicked()
{
//    exit(0);
  if(ros_terminal)
  {
    qDebug()<<"running";
    ros_terminal->terminate();
    if(ros_terminal->waitForFinished(-1)) qDebug()<<"terminated";

  }
  else qDebug()<<"stop";
//  if(ros_terminal->ProcessState==1) qDebug()<<"running";
}

void MainWindow::QuitPtn_clicked()
{

  if(ros_terminal)
  {
    qDebug()<<"running";
    ros_terminal->terminate();

  }
  else qDebug()<<"stop";
   exit(0);
//  if(ros_terminal->ProcessState==1) qDebug()<<"running";
}

void MainWindow::readSerial()
{
    ui->plainTextEdit->appendPlainText(terminal->readAll());
    QString getSerial=ui->plainTextEdit->toPlainText();
    QStringList list=getSerial.split("\n",QString::SkipEmptyParts);
    ui->SerialComboBox->addItems(list);
    qDebug()<<getSerial;
}

void MainWindow::refresh()
{
  if(ui->topic1->isChecked()) qDebug()<<"1";
  //else qDebug()<<"2";
  if(ui->topic2->isChecked()) qDebug()<<"3";
}

void MainWindow::ReadOutput()
{
   ui->plainTextEdit->appendPlainText(ros_terminal->readAll());
}
