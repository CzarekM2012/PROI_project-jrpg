#include "maptile.h"
#include <QLabel>
#include <QString>
#include <QPixmap>

MapTile::MapTile(int x, int y, QString pix, QWidget *parent, bool walk, bool event) : QWidget(parent)
{
  coord_x = x;
  coord_y = y;
  tile_w = 100;
  tile_h = 100;
  this->setGeometry(coord_x, coord_y, tile_w, tile_h);
  has_event = event;
  walkable = walk;
  tile_pic_pix = QPixmap(pix);
  tile_pic_pix = tile_pic_pix.scaled(tile_w, tile_h);
  tile_pic = new QLabel(this);
  tile_pic->setPixmap(tile_pic_pix);
  tile_pic->setFrameStyle(1);

  up_neigh = nullptr;
  down_neigh = nullptr;
  l_neigh = nullptr;
  r_neigh = nullptr;

}

  void MapTile::set_neighbors(MapTile *up, MapTile *down, MapTile *l, MapTile *r)
  {
    up_neigh = up;
    down_neigh = down;
    l_neigh = l;
    r_neigh = r;
    return;
  }
