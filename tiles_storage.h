#ifndef TILES_STORAGE_H
#define TILES_STORAGE_H
#include "switchable_frame.h"
#include "maptile.h"


struct tile_descriptor
{
  tile_descriptor(QString a, bool b = true, bool c = false, int d = -1)
  {pic = a; walkable = b; has_event = c; new_map = d;}
    QString pic;
    bool walkable;
    bool has_event;
    int new_map;
};

class tiles_storage : public switchable_frame
{
public:
  tiles_storage(int tileset);
  std::vector<maptile*> tiles;
  void init_tiles(int tileset);
  int* load_tileset(int *map, int *events, std::string path);
  void set_all_neighbors();
  void place_children();

};

#endif // TILES_STORAGE_H
