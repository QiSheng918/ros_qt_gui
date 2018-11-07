#include "../include/data_plot.h"
#include <QDateTime>
#include <QDebug>

data_plot::data_plot()
{

}


data_plot::data_plot(QCustomPlot *q)
{
  node=new ros_node();
  qCustomPlot_curve=q;
  qCustomPlot_curve->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);
  qCustomPlot_curve->xAxis->setLabel(QStringLiteral("time/s"));
  qCustomPlot_curve->yAxis->setLabel(QStringLiteral(""));
//  qCustomPlot_curve->legend->setFont(QFont("Helvetica",8));
  qCustomPlot_curve->legend->setRowSpacing(0);
  qCustomPlot_curve->legend->setMargins(QMargins(3,3,3,3));
  for(int i=0;i<3;i++)
  {
    if(i==3) topic_sEMG_data=false;
    else  topic_IMU_data[i]=false;
    graph_num[i]=-1;
  }

  PlotTimer=new QTimer();
  connect(PlotTimer,SIGNAL(timeout()),this,SLOT(plot_curve()));
  PlotTimer->start(10);

}
data_plot::~data_plot()
{
  delete node;
//  delete qCustomPlot_curve;
}

//void data_plot::run()
//{}
void data_plot::plot_curve()
{
  node->time_reset[0]=topic_IMU_data[0]||topic_IMU_data[1]||topic_IMU_data[2];
  node->time_reset[1]=topic_sEMG_data;
  if(!topic_IMU_data[0]&&!topic_IMU_data[1]&&!topic_IMU_data[2]&&!topic_sEMG_data)
  {
    qCustomPlot_curve->xAxis->setRange(0,8);

    qCustomPlot_curve->legend->setVisible(false);
    for(int i=0;i<4;i++) graph_num[i]=-1;
    qCustomPlot_curve->clearGraphs();
    qCustomPlot_curve->replot();
  }
  else
  {
     if(topic_IMU_data[0]){
       if(graph_num[0]==-1) {
         qCustomPlot_curve->addGraph( );
         graph_num[0]=qCustomPlot_curve->graphCount()-1;
       }
       qCustomPlot_curve->graph(graph_num[0])->setPen(QPen(Qt::blue));
       qCustomPlot_curve->graph(graph_num[0])->setName("IMU_data[0]");
       qCustomPlot_curve->graph(graph_num[0])->addData(node->IMU_t, node->IMU_data[0]);
     }
     else{
       if(graph_num[0]!=-1) {
         qCustomPlot_curve->graph(graph_num[0])->clearData();
         qCustomPlot_curve->removeGraph(graph_num[0]);
         updateGraphNum(0);
       }
     }

     if(topic_IMU_data[1]){
       if(graph_num[1]==-1) {
         qCustomPlot_curve->addGraph( );
         graph_num[1]=qCustomPlot_curve->graphCount()-1;
       }
       qCustomPlot_curve->graph(graph_num[1])->setPen(QPen(Qt::red));
       qCustomPlot_curve->graph(graph_num[1])->setName("IMU_data[1]");
       qCustomPlot_curve->graph(graph_num[1])->addData(node->IMU_t, node->IMU_data[1]);
     }
     else{
       if(graph_num[1]!=-1) {
                  qCustomPlot_curve->graph(graph_num[1])->clearData();
         qCustomPlot_curve->removeGraph(graph_num[1]);
         updateGraphNum(1);
       }
     }

     if(topic_IMU_data[2]){
       if(graph_num[2]==-1) {
         qCustomPlot_curve->addGraph( );
         graph_num[2]=qCustomPlot_curve->graphCount()-1;

       }
       qCustomPlot_curve->graph(graph_num[2])->setPen(QPen(Qt::green));
       qCustomPlot_curve->graph(graph_num[2])->setName("IMU_data[2]");
       qCustomPlot_curve->graph(graph_num[2])->addData(node->IMU_t, node->IMU_data[2]);
     }
     else{
       if(graph_num[2]!=-1) {
         qCustomPlot_curve->graph(graph_num[2])->clearData();
         qCustomPlot_curve->removeGraph(graph_num[2]);
         updateGraphNum(2);
       }
     }

     if(topic_sEMG_data){
       if(graph_num[3]==-1) {
         qCustomPlot_curve->addGraph( );
         graph_num[3]=qCustomPlot_curve->graphCount()-1;
       }
       qCustomPlot_curve->graph(graph_num[3])->setPen(QPen(Qt::black));
       qCustomPlot_curve->graph(graph_num[3])->setName("temp");
       qCustomPlot_curve->graph(graph_num[3])->addData(node->t, node->temp);
     }
     else{
       if(graph_num[3]!=-1) {
                  qCustomPlot_curve->graph(graph_num[3])->clearData();
         qCustomPlot_curve->removeGraph(graph_num[3]);
         updateGraphNum(3);
       }
     }
     qCustomPlot_curve->legend->setVisible(true);
     if(node->IMU_t<6)   qCustomPlot_curve->xAxis->setRange(0,8);
     else qCustomPlot_curve->xAxis->setRange(node->IMU_t-6,node->IMU_t+2);
     qCustomPlot_curve->replot();

  }
}



void data_plot::updateGraphNum(int k)
{
  for(int i=0;i<4;i++)
  {
    if(graph_num[i]>graph_num[k])graph_num[i]--;
  }
  graph_num[k]=-1;
}

void data_plot::setTopic_true(int i)
{
    switch(i){
      case 0: topic_IMU_data[0]=true;  break;
      case 1: topic_IMU_data[1]=true;  break;
      case 2: topic_IMU_data[2]=true;  break;
    default:  topic_sEMG_data=true;
    }
}

void data_plot::setTopic_false(int i)
{
  switch(i){
    case 0: topic_IMU_data[0]=false;  break;
    case 1: topic_IMU_data[1]=false;  break;
    case 2: topic_IMU_data[2]=false;  break;
  default:  topic_sEMG_data=false;
  }
}
