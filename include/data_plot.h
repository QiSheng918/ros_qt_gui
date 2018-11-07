#ifndef DATA_PLOT_H
#define DATA_PLOT_H

#include <QWidget>
#include <QThread>
#include "qcustomplot.h"
#include <QTimer>
#include "ros_node.h"
#include<QTime>

class data_plot:public QObject
{
  Q_OBJECT
public:
  data_plot();
  data_plot(QCustomPlot *q);
  ~data_plot();
  void setTopic_true(int i);
  void setTopic_false(int i);

private slots:
  void plot_curve();

private:
  QCustomPlot *qCustomPlot_curve;
  QTimer *PlotTimer;

  ros_node *node;
  bool topic_IMU_data[3];
  bool topic_sEMG_data;
  int graph_num[4];

  void updateGraphNum(int k);
  void run();
};

#endif // DATA_PLOT_H
