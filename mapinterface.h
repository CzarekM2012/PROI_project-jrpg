#ifndef MAPINTERFACE_H
#define MAPINTERFACE_H
#include <QPushButton>
#include "switchable_frame.h"
#include "maptile.h"
#include "playeronmap.h"

struct tile_descriptor
{
  tile_descriptor(QString a, bool b = true, bool c = false)
  {pic = a; walkable = b; has_event = c;}
    QString pic;
    bool walkable;
    bool has_event;
};

class mapinterface : public switchable_frame
{
    Q_OBJECT
public:
  mapinterface(int tileset);
  std::vector<maptile*> tiles;
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
  void init_tiles(int tileset);
  void set_all_neighbors();
  void set_all_events(int tileset);
  int* load_tileset(int *map, std::string path);
  void create_children();
  void place_children();
  void connect_signals();

};

#endif // MAPINTERFACE_H
