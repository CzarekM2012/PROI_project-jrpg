#ifndef MAPTILE_H
#define MAPTILE_H
#include <QFrame>
#include <QLabel>


class maptile: public QFrame
{
  Q_OBJECT
public:
  maptile(int x, int y, QString pix, bool walk = true, bool event = false, int nmap = -1);
  int coord_x, coord_y;
  int tile_w, tile_h, new_map;
  bool has_event, walkable, is_curr_tile = false;
  QPixmap tile_pic_pix;
  QLabel *tile_pic;

  maptile *up_neigh;
  maptile *down_neigh;
  maptile *l_neigh;
  maptile *r_neigh;

  void set_neighbors(maptile *up, maptile *down, maptile *l, maptile *r);

signals:

};

#endif // MAPTILE_H
