#include "bglabel.h"
#include <QApplication>
#include <QPushButton>

BgLabel::BgLabel(QWidget *parent) : QWidget(parent)
{
  next = new QPushButton("Not Clicked", this);
  next->setGeometry(30, 30, 150, 50);
}
