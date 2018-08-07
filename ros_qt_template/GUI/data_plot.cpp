#include "data_plot.h"
#include <QDateTime>
#include <QDebug>

data_plot::data_plot()
{

}

data_plot::data_plot(QCustomPlot *q)
{
  node=new sub_node();
  p=q;
  dataTimer=new QTimer();
  connect(dataTimer,SIGNAL(timeout()),this,SLOT(begin_plot()));
  dataTimer->start(0);
}
void data_plot::begin_plot()
{

//  p->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);   //可拖拽+可滚轮缩放

//  p->legend->setVisible(true);
//  p->xAxis->setLabel(QStringLiteral("X轴文字"));
//  p->yAxis->setLabel(QStringLiteral("Y轴文字"));

//  p->xAxis->setRange(0,100);
//  p->yAxis->setRange(0,10);

//  p->addGraph();
//  p->addGraph();
//  p->graph(0)->setPen(QPen(Qt::red));
//  p->graph(1)->setPen(QPen(Qt::blue));

//  for(int i=0;i<100;i++)
//  {
//      p->graph(0)->addData(i, i%10);
//      p->graph(1)->addData(i, (double)i/10.0);
//  }
   //key的单位是秒
//      double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
//      qsrand(QTime::currentTime().msec() + QTime::currentTime().second() * 10000);
//      //使用随机数产生两条曲线
//      double value0 = qrand() % 100;
//      double value1 = qrand() % 80;
      p->addGraph();
      p->graph(0)->setPen(QPen(Qt::blue));
      p->graph(0)->setName("temp");
      p->graph(0)->addData(node->t, node->linear);//添加数据1到曲线1
//      p->legend->setVisible(true);
      p->xAxis->setLabel(QStringLiteral("time/s"));
      p->yAxis->setLabel(QStringLiteral(""));
//      p->addGraph();
//      p->graph(1)->setPen(QPen(Qt::red));
//      p->graph(1)->setName("nm");
//          p->graph(1)->addData(key, value1);//添加数据2到曲线2
      if(node->t>10) p->graph(0)->removeDataBefore(node->t-10);

      p->graph(0)->rescaleValueAxis();
//      p->graph(1)->rescaleValueAxis(true);
//      qDebug()<<node->linear;
      //这里的8，是指横坐标时间宽度为8秒，如果想要横坐标显示更多的时间
      //就把8调整为比较大到值，比如要显示60秒，那就改成60。
      //这时removeDataBefore(key-8)中的8也要改成60，否则曲线显示不完整。
      p->xAxis->setRange(node->t+0.25, node->t+10, Qt::AlignRight);//设定x轴的范围
      p->replot();

}
