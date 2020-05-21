#include "playeronmap.h"
#include <QLabel>
#include "maptile.h"

PlayerOnMap::PlayerOnMap(MapTile *start, QWidget *parent) : QWidget(parent)
{
  curr_tile = start;
  this->setGeometry(10, 10, 800, 600);
  face = new QLabel(this);
  face->setGeometry(curr_tile->coord_x, curr_tile->coord_y, 80, 80);

  QString fstring = ":/images/face1.png";
  QPixmap fimg = QPixmap(fstring);
  fimg = fimg.scaled(80, 70);
  face->setPixmap(fimg);
}
