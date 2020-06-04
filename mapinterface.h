#ifndef MAPINTERFACE_H
#define MAPINTERFACE_H
#include <QPushButton>
#include "switchable_frame.h"
#include "maptile.h"
#include "playeronmap.h"
#include "tiles_storage.h"


class mapinterface : public switchable_frame
{
    Q_OBJECT
public:
  mapinterface(int tileset, int player_state);
  tiles_storage *tiles;
  //  std::vector<maptile*> tiles;
  QPushButton *up;
  QPushButton *down;
  QPushButton *left;
  QPushButton *right;
  playeronmap *player;

private slots:
 void slotButtonUp();
 void slotButtonDown();
 void slotButtonLeft();
 void slotButtonRight();

private:
  void set_all_neighbors();
  void set_all_events(int tileset);
  int* load_tileset(int *map, std::string path);
  void create_children();
  void place_children();
  void connect_signals();

signals:
  void change_map(int m, int p);

};

#endif // MAPINTERFACE_H
