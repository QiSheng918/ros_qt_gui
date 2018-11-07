#include "../include/mainwindow.h"
//#include "ui_mainwindow.h"
#include "stdio.h"


#define str_dir QString("/dev/serial/by-path")

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("ros_qt_template");

    viz=new MyViz();
    ui->VizArea->addSubWindow(viz, Qt::FramelessWindowHint); // FramelessWindowHint removes close, minimize and maximize title bar
    viz->showMaximized();

    RobotModelFlag=false;

    DataPlot=new data_plot(ui->qcustomplotWidget);

    ros_terminal=new QProcess(this);
    rqt_terminal=new QProcess(this);

    messageBox=new MyMessageBox;
    messageBox->setIcon(QMessageBox::NoIcon);
    messageBox->setDefaultButton(0);
    messageBox->setWindowTitle("Information");
    messageBox->setText("2333");
   // messageBox->setGeometry(400,600,400,600);
    messageBox->setMySize(200,100);
//    messageBox->show();
    messageBox->setModal(true);

    this->setMouseTracking(true);
    ui->dockWidget_left->setMouseTracking(true);

    ServicePub=new ros_service_pub;
    python_terminal=new QProcess(this);
    BluetoothDir=new QDir(str_dir);
    BluetoothDir->setFilter(QDir::Files);
    ui->SerialComboBox->addItems(BluetoothDir->entryList());
    ui->showButton->setVisible(false);
    UpdateTimer=new QTimer();
    connect(UpdateTimer,SIGNAL(timeout()),this,SLOT(update()));
    UpdateTimer->start(50);

    connect(ui->StartButton,SIGNAL(clicked()),this,SLOT(StartPtn_clicked()));
    connect(ui->StopButton,SIGNAL(clicked()),this,SLOT(StopPtn_clicked()));
    connect(ui->QuitButton,SIGNAL(clicked()),this,SLOT(QuitPtn_clicked()));
    connect(ui->ArmButton,SIGNAL(clicked()),this,SLOT(PythonPth_clicked()));
    connect(ros_terminal,SIGNAL(readyRead()),this,SLOT(ReadOutput()));
    connect(python_terminal,SIGNAL(readyRead()),this,SLOT(readOutput()));
    connect(ui->textBrowser,SIGNAL(textChanged()),this,SLOT(textBrower_textChanged()));
    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(Ptn_clicked()));
//    connect(ServicePub,SIGNAL(get_refer(int)),this,SLOT(display_refer(int)));
    connect(ui->rqtButton,SIGNAL(clicked()),this,SLOT(RqtPtn_clicked()));
   // connect(ros_terminal,SIGNAL(started()),viz,SLOT(addRobotModel()));
    ui->sEMG_data_checkBox->setDisabled(true);
    ui->IMU_data0_checkBox->setDisabled(true);
    ui->IMU_data1_checkBox->setDisabled(true);
    ui->IMU_data2_checkBox->setDisabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete viz;
    delete DataPlot;

    if(ros_terminal->state()!=0)   ros_terminal->terminate();
    delete ros_terminal;

    if(python_terminal->state()!=0)   python_terminal->terminate();
    delete python_terminal;

    if(rqt_terminal->state()!=0)  rqt_terminal->terminate();
    delete rqt_terminal;

    delete UpdateTimer;
    delete BluetoothDir;
    delete ServicePub;
}



void MainWindow::StartPtn_clicked()
{
    if(ros_terminal->state()!=0)  ui->VizArea->update();
    else{
        QString run_cmd = QString("roslaunch urdf_tutorial myrobot_display.launch");
      //    + QString("urdf_tutorial") + QString(" ")
       //   + QString("myrobot_display.launch");
        int n = run_cmd.length()+1;
        char cmd[n];
        std::string cmd_string = run_cmd.toStdString();
        strncpy(cmd,cmd_string.c_str(),n-1);
        cmd[n-1] =0;
        qDebug()<<cmd;
        ros_terminal->start(cmd);
      if(ros_terminal->waitForStarted(-1))
      {
        qDebug()<<"started";
        qDebug()<<ros_terminal->state();
//        viz->addRobotModel();
//        viz->removeRobotModel();
//        viz->addRobotModel();
//        sleep(0.5);
      //  viz->addRobotModel();
        RobotModelFlag=true;
        initTime=QTime::currentTime();
        qDebug()<<ros_terminal->children();

      }
      qDebug()<<"2333";
      qDebug()<<ros_terminal->children();
    }

}



void MainWindow::StopPtn_clicked()
{
    qDebug()<<ros_terminal->state();
    if(ros_terminal->state()!=0){
        ros_terminal->terminate();

       // ros_terminal->kill();
    //    if(ros_terminal->waitForFinished(-1)) qDebug()<<"terminated";
    }
    qDebug()<<ros_terminal->state();
   // QMessageBox::information(this,"this",ServicePub->getRefer());
   viz->removeRobotModel();
}



void MainWindow::QuitPtn_clicked()
{
//   if(bluetooth_terminal->state()!=0)   bluetooth_terminal->terminate();
    if(ros_terminal->state()!=0)
    {
      ros_terminal->terminate();
      ros_terminal->kill();
    }
    if(python_terminal->state()!=0)   python_terminal->terminate();
    QProcess node_kill;

      QString run_cmd = QString("rosnode ")
              + QString("kill") + QString(" ")
              + QString("-a");
            int n = run_cmd.length()+1;
            char cmd[n];
            std::string cmd_string = run_cmd.toStdString();
            strncpy(cmd,cmd_string.c_str(),n-1);
            cmd[n-1] =0;
           // qDebug()<<cmd;
            node_kill.start(run_cmd);
//      while(node_kill.waitForStarted(-1)){}
    exit(0);
}

void MainWindow::PythonPth_clicked()
{

    QString run_cmd = QString("rosrun ")
      + QString("armlet_c") + QString(" ")
      + QString("run.py");
    int n = run_cmd.length()+1;
    char cmd[n];
    std::string cmd_string = run_cmd.toStdString();
    strncpy(cmd,cmd_string.c_str(),n-1);
    cmd[n-1] =0;
    qDebug()<<cmd;
    python_terminal->start(cmd);
    ui->SerialComboBox->setDisabled(true);
//    messageBox->setDefaultButton(0);
//    messageBox->show();
//     messageBox->addButton(QMessageBox::Ok);
}

void MainWindow::Ptn_clicked()
{
//  if(python_terminal->state()!=0){
//      python_terminal->terminate();
//  //    if(ros_terminal->waitForFinished(-1)) qDebug()<<"terminated";
//  }
//  qDebug()<<python_terminal->state();
  viz->addRobotModel();
}

void MainWindow::RqtPtn_clicked()
{
  QString run_cmd = QString("rosrun ")
    + QString("rqt_plot") + QString(" ")
    + QString("rqt_plot");
  int n = run_cmd.length()+1;
  char cmd[n];
  std::string cmd_string = run_cmd.toStdString();
  strncpy(cmd,cmd_string.c_str(),n-1);
  cmd[n-1] =0;
  qDebug()<<cmd;
  rqt_terminal->start(cmd);
  qDebug()<<rqt_terminal->state();
  rqt_terminal->waitForStarted(-1);
  qDebug()<<rqt_terminal->state();
//  ui->SerialComboBox->setDisabled(true);
}

void MainWindow::update()
{
    if(ui->IMU_data0_checkBox->isChecked()) DataPlot->setTopic_true(0);
    else  DataPlot->setTopic_false(0);

    if(ui->IMU_data1_checkBox->isChecked()) DataPlot->setTopic_true(1);
    else  DataPlot->setTopic_false(1);

    if(ui->IMU_data2_checkBox->isChecked()) DataPlot->setTopic_true(2);
    else  DataPlot->setTopic_false(2);

    if(ui->sEMG_data_checkBox->isChecked()) DataPlot->setTopic_true(3);
    else  DataPlot->setTopic_false(3);

    QStringList str_list;
    str_list.clear();
    for(int i=0;i<ui->SerialComboBox->count();i++)
    {
       str_list+=ui->SerialComboBox->itemText(i);
    }

    BluetoothDir->setPath(str_dir);
//    qDebug()<<BluetoothDir->entryList();

    if(str_list!=BluetoothDir->entryList())
    {
      ui->SerialComboBox->clear();
      ui->SerialComboBox->addItems(BluetoothDir->entryList());
    }
    if(python_terminal->state()==0)  ui->SerialComboBox->setDisabled(false);
    SerialNumber=ui->SerialComboBox->currentText();
    ServicePub->setSerialNumber(std::string((const char *)SerialNumber.toLocal8Bit()));

    ui->textBrowser->moveCursor(QTextCursor::End);

    if(ServicePub->getRefer()=="Start Control")
    {
      ui->sEMG_data_checkBox->setDisabled(false);
      ui->IMU_data0_checkBox->setDisabled(false);
      ui->IMU_data1_checkBox->setDisabled(false);
      ui->IMU_data2_checkBox->setDisabled(false);
    }

//    if(ros_terminal->state()!=0)
//    {
//      viz->addRobotModel();
//    }
//    else
//    {
//      viz->removeRobotModel();
//    }
     int t=initTime.msecsTo(QTime::currentTime());
     if(t>=1500 && RobotModelFlag)
     {
       viz->addRobotModel();
       RobotModelFlag=false;
     }

}

void MainWindow::ReadOutput()
{
//   ui->plainTextEdit->appendPlainText(ros_terminal->readAll());
    ui->textBrowser->setText(ros_terminal->readAll());

    qDebug()<<ros_terminal->readAll();
}


void MainWindow::readOutput()
{
//   ui->plainTextEdit->appendPlainText(ros_terminal->readAll());
    ui->textBrowser->setText(python_terminal->readAll());

    qDebug()<<python_terminal->readAll();
}

//void MainWindow::mouseDoubleClickEvent(QMouseEvent *event)
//{
//  if(event->x()>800) ui->dockWidget_right->setVisible(true);
//}

void MainWindow::textBrower_textChanged()
{
    ui->textBrowser->moveCursor(QTextCursor::End);
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
 // if(event->x()>400)  ui->showButton->setVisible(true);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
 // qDebug()<<ui->dockWidget_left->geometry();
  if(ui->dockWidget_right->isVisible())
  {
    event->ignore();
    ui->showButton->setVisible(false);
  }
  else{
    QRect rect=ui->dockWidget_left->geometry();
    if(event->x()<rect.right() &&event->x()>(rect.right()-25))  ui->showButton->setVisible(true);
    else ui->showButton->setVisible(false);
  }
}

