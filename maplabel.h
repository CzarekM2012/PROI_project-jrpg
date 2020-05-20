#ifndef MAPLABEL_H
#define MAPLABEL_H

#include <QWidget>
#include <vector>

class MapTile;
class QPushButton;
class MapLabel : public QWidget
{
  Q_OBJECT
public:
  explicit MapLabel(int tileset, QWidget *parent = nullptr);

  std::vector<MapTile*> tiles;
  QPushButton *up;
  QPushButton *down;
  QPushButton *left;
  QPushButton *right;

private:
  void init_tiles(int tileset);
  void set_all_neighbors();

};

#endif // MAPLABEL_H
