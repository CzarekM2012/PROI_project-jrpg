#include "dialog_window.h"
#include "bglabel.h"
#include "maplabel.h"
#include <QApplication>
#include <QPushButton>
#include <QLabel>

dialog_window::dialog_window(QWidget *parent) : QWidget(parent)
{
 //background = new BgLabel(1, this);
 //background = new BgLabel(0, this);
  map = new MapLabel(0, this);
}
