#include "maptile.h"
#include <QLabel>
#include <QString>
#include <QPixmap>

maptile::maptile(int x, int y, QString pix, bool walk, bool event, int nmap, int d)
{
  coord_x = x;
  coord_y = y;
  tile_w = 90; //80
  tile_h = 90; //80
  d_event = d;
  if(d_event >= 0)
    {
      has_event = true;
    }
  else
    {
      has_event = event;
    }
  walkable = walk;
  new_map = nmap;
  setStyleSheet(QString("border-image:url(") + pix + QString(")"));

  up_neigh = nullptr;
  down_neigh = nullptr;
  l_neigh = nullptr;
  r_neigh = nullptr;

}

  void maptile::set_neighbors(maptile *up, maptile *down, maptile *l, maptile *r)
  {
    up_neigh = up;
    down_neigh = down;
    l_neigh = l;
    r_neigh = r;
    return;
  }
