#ifndef MAPLABEL_H
#define MAPLABEL_H

#include <QWidget>
#include <vector>

class BgLabel;
class PlayerOnMap;
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
  PlayerOnMap *player;
  BgLabel *curr_event;

private slots:
 void slotButtonUp();
 void slotButtonDown();
 void slotButtonLeft();
 void slotButtonRight();

private:
  void init_tiles(int tileset);
  void set_all_neighbors();

};

#endif // MAPLABEL_H
