#include "playeronmap.h"
#include <QLabel>
#include "maptile.h"

playeronmap::playeronmap(maptile *start, QWidget *parent)
{
  curr_tile = start;
  //setGeometry(0, 0, parent->width(), parent->height());
  //face = new QLabel(this);
  //face->setGeometry(curr_tile->coord_x, curr_tile->coord_y, parent->width(), parent->height());
  //face->setStyleSheet(QString("border-image:url(:/images/face1.png)"));
/*
  QString fstring = ":/images/face1.png";
  QPixmap fimg = QPixmap(fstring);
  fimg = fimg.scaled(80, 70);
  face->setPixmap(fimg);
  */
}
