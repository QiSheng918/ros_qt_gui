#include "../include/mymessagebox.h"


MyMessageBox::MyMessageBox(QWidget *parent) :
    QMessageBox(parent),
    _width(0),
    _height(0)
{
}

MyMessageBox::~MyMessageBox()
{

}

void MyMessageBox::setMySize(int width, int height)
{
    _width = width;
    _height = height;
}

void MyMessageBox::resizeEvent(QResizeEvent *event)
{
    setFixedSize(_width, _height);
}
