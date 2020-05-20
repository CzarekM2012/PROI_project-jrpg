#ifndef MAPTILE_H
#define MAPTILE_H

#include <QWidget>

class QLabel;
class MapTile : public QWidget
{
  Q_OBJECT
public:
  explicit MapTile(int x, int y, QString pix, QWidget *parent = nullptr, bool walk = true, bool event = false);
  int coord_x;
  int coord_y;
  int tile_w;
  int tile_h;
  bool has_event;
  bool walkable;
  QPixmap tile_pic_pix;
  QLabel *tile_pic;

  MapTile *up_neigh;
  MapTile *down_neigh;
  MapTile *l_neigh;
  MapTile *r_neigh;

  void set_neighbors(MapTile *up, MapTile *down, MapTile *l, MapTile *r);

signals:

};

#endif // MAPTILE_H
