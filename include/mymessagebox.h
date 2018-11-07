#ifndef MYMESSAGEBOX_H
#define MYMESSAGEBOX_H

#include<QMessageBox>
#include<QShowEvent>

class MyMessageBox:public QMessageBox
{
public:
  explicit MyMessageBox(QWidget *parent = 0);
  ~MyMessageBox();
  void setMySize(int width, int height);

//protected:
//  void showEvent(QShowEvent* event){
//    QMessageBox::showEvent(event);
//    this->setFixedSize(800, 1000);
//  }
protected:
    void resizeEvent(QResizeEvent *event);

private:
    int _width;
    int _height;

};

#endif // MYMESSAGEBOX_H
