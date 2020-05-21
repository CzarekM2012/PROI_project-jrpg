#ifndef PLAYERONMAP_H
#define PLAYERONMAP_H

#include <QWidget>

class QLabel;
class MapTile;
class PlayerOnMap : public QWidget
{
  Q_OBJECT
public:
  explicit PlayerOnMap(MapTile *start, QWidget *parent = nullptr);
  MapTile *curr_tile;
  QLabel *face;

};

#endif // PLAYERONMAP_H
