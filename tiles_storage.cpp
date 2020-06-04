#include "tiles_storage.h"
#include <fstream>

tiles_storage::tiles_storage(int tileset)
{
  init_tiles(tileset);
  place_children();
  set_all_neighbors();
}

int* tiles_storage::load_tileset(int *map, std::string path)
  /*
  Loads tileset from a file.
  */
  {
     std::ifstream readfile(path);
     std::string line;

     for (int i = 0; i<70; i++)
       {
         int num;
         readfile >> num;
         map[i] = num;
       }

     return map;
  }

//DO POPRAWIENIA
void tiles_storage::init_tiles(int tileset)
{
//int tileset: 0=plains, 1=sand forest, 2=ruins
  QString tf = ":/images/";
  std::vector<tile_descriptor> all_tiles = {{":/images/grass_bg.png"}, {":/images/trees_bg.png", false}, {":/images/path_dirt_bg.png"},
                                            {":/images/stone_bg.png"}, {":/images/water_bg.png", false}, {":/images/water_corner_bg.png", false}, {":/images/water_edge_bg.png", false},
                                            {":/images/water_edge_vert_bg.png", false}, {":/images/house_bg.png"}, {":/images/sand1_bg.png"}, {":/images/sand2_bg.png"},
                                            {":/images/bush_bg.png", false}, {":/images/cactus_bg.png"}, {":/images/oasis_bg.png"},
                                            {":/images/rock_bg.png", false}, {":/images/rock_hand_bg.png", false}, {":/images/rock_2hands_bg.png", false},
                                            {":/images/path_dirt_bg.png", true, true, 1}, {":/images/sand2_bg.png", true, true, 0}};

   int tileset0[70];
if(tileset == 0)
  {
    load_tileset(tileset0, "map0.txt");
  }
else if(tileset == 1)
  {
    load_tileset(tileset0, "map1.txt");
  }
else if(tileset == 2)
  {
    load_tileset(tileset0, "map2.txt");
  }
    maptile* new_tile;
    int pctr = 0;

    for(int j=0; j<7; j++)
      {
        for(int i=0; i<10; i++)
        {
        new_tile = new maptile(i, j, all_tiles[tileset0[pctr]].pic, all_tiles[tileset0[pctr]].walkable,
                               all_tiles[tileset0[pctr]].has_event, all_tiles[tileset0[pctr]].new_map);
        pctr++;
        tiles.push_back(new_tile);
        }
      }

  return;
 }

void tiles_storage::place_children()
{
    int k = 0;
    for(int j = 0; j < 7; j++)
      {
        for(int i = 0; i < 10; i++)
          {
            layout_->addWidget(tiles[k], j, i);
            k++;
          }
      }
}

void tiles_storage::set_all_neighbors()
{
  for (int i = 0; i<70; i++)
    {
      if(i < 10)
        tiles[i]->up_neigh = nullptr;
      else
        tiles[i]->up_neigh = tiles[i-10];

      if(i >= 60)
        tiles[i]->down_neigh = nullptr;
      else
        tiles[i]->down_neigh = tiles[i+10];

      if(i%10 == 0)
        tiles[i]->l_neigh = nullptr;
      else
        tiles[i]->l_neigh = tiles[i-1];

      if((i-9)%10 == 0)
        tiles[i]->r_neigh = nullptr;
      else
        tiles[i]->r_neigh = tiles[i+1];
    }
  return;

}
