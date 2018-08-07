#ifndef DATA_PLOT_H
#define DATA_PLOT_H

#include <QWidget>
#include "qcustomplot.h"
#include <QTimer>
#include "sub_node.h"

class data_plot:public QObject
{
  Q_OBJECT
public:
  data_plot();
  data_plot(QCustomPlot *q);
private slots:
  void begin_plot();
private:
  QCustomPlot *p;
  QTimer *dataTimer;
  sub_node *node;
};

#endif // DATA_PLOT_H
