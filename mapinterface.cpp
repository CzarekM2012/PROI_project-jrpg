#include <fstream>
#include "mapinterface.h"

mapinterface::mapinterface(int tileset)
  {
      init_tiles(tileset);
      set_all_neighbors();
      create_children();
      place_children();
      connect_signals();
      player = new playeronmap(tiles[27], this);
      layout_->addWidget(player, player->curr_tile->coord_y, player->curr_tile->coord_x);
  }

  void mapinterface::create_children()
  {
    up = new QPushButton("^");
    down = new QPushButton("V");
    left = new QPushButton("<-");
    right = new QPushButton("->");
    /*
    up->setFixedSize(80, 80); //50
    down->setFixedSize(80, 80); //50
    left->setFixedSize(80, 80); //50
    right->setFixedSize(80, 80); //50
    */
  }

  int* mapinterface::load_tileset(int *map, std::string path)
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
  void mapinterface::init_tiles(int tileset)
  {
  //int tileset: 0=plains, 1=sand forest, 2=ruins
    QString tf = ":/images/";
    std::vector<tile_descriptor> all_tiles = {{":/images/grass_bg.png"}, {":/images/trees_bg.png", false}, {":/images/path_dirt_bg.png"},
                                      {":/images/stone_bg.png"}, {":/images/water_bg.png", false}, {":/images/water_corner_bg.png", false}, {":/images/water_edge_bg.png", false},
                                      {":/images/water_edge_vert_bg.png", false}, {":/images/house_bg.png"}, {":/images/sand1_bg.png"}, {":/images/sand2_bg.png"},
                                     {":/images/bush_bg.png", false}, {":/images/cactus_bg.png"}, {":/images/oasis_bg.png"},
                                     {":/images/rock_bg.png", false}, {":/images/rock_hand_bg.png", false}, {":/images/rock_2hands_bg.png", false}};

    //int tileset0[70];
    //std::string dfud = ":/texts/map0.txt";
    //load_tileset(tileset0, dfud);
//    tile_descriptor a = {":/images/grass_bg.png", true, false};

    int tileset0[70] = {1, 1, 1, 2, 1, 0, 1, 1, 1, 1,
                        1, 1, 0, 2, 0, 0, 0, 1, 1, 1,
                        1, 0, 0, 2, 0, 0, 1, 8, 1, 0,
                        1, 0, 2, 2, 0, 1, 1, 0, 0, 3,
                        0, 0, 2, 0, 1, 1, 0, 3, 0, 0,
                        0, 2, 2, 0, 1, 0, 0, 0, 0, 1,
                        0, 2, 0, 3, 0, 0, 5, 7, 7, 7};

    int tileset1[70] = {9, 12, 9, 9, 9, 9, 9, 9, 11, 11,
                        9, 9, 10, 9, 13, 10, 9, 10, 9, 11,
                        11, 11, 9, 9, 9, 9, 11, 9, 9, 9,
                        11, 15, 11, 9, 9, 11, 11, 9, 12, 10,
                        11, 9, 9, 10, 9, 11, 16, 9, 9, 9,
                        9, 9, 12, 9, 9, 9, 11, 11, 9, 9,
                        9, 10, 9, 9, 11, 11, 11, 11, 11, 9};

  if(tileset == 0)
    {
      maptile* new_tile;
      int pctr = 0;

      for(int j=0; j<7; j++)
        {
          for(int i=0; i<10; i++)
          {
          new_tile = new maptile(i, j, all_tiles[tileset0[pctr]].pic, all_tiles[tileset0[pctr]].walkable);
          pctr++;
          tiles.push_back(new_tile);
          }
        }
    }
    return;
   }

  void mapinterface::set_all_neighbors()
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

  void mapinterface::place_children()
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
      layout_->addWidget(up, 3, 12);
      layout_->addWidget(down, 5, 12);
      layout_->addWidget(left, 4, 11);
      layout_->addWidget(right, 4, 13);
  }

  void mapinterface::connect_signals()
  {
    connect(up, SIGNAL (clicked(bool)), this, SLOT (slotButtonUp()));
    connect(down, SIGNAL (clicked(bool)), this, SLOT (slotButtonDown()));
    connect(left, SIGNAL (clicked(bool)), this, SLOT (slotButtonLeft()));
    connect(right, SIGNAL (clicked(bool)), this, SLOT (slotButtonRight()));
    return;
  }

  void mapinterface::slotButtonUp()
  {
    if(player->curr_tile->up_neigh != 0)
      {
        if(player->curr_tile->up_neigh->walkable == true)
          {
            player->curr_tile = player->curr_tile->up_neigh;
            layout_->addWidget(player, player->curr_tile->coord_y, player->curr_tile->coord_x);
 //           player->face->setGeometry(player->curr_tile->coord_x, player->curr_tile->coord_y, 90, 90);
 /*           if(player->curr_tile->has_event == true)
              {
              player->curr_tile->has_event = false;
              curr_event = new BgLabel(player->curr_tile->dialog_event, this);
              curr_event->show();
              }*/
          }
      }
    return;
  }

  void mapinterface::slotButtonDown()
  {
    if(player->curr_tile->down_neigh != 0)
      {
        if(player->curr_tile->down_neigh->walkable == true)
          {
            player->curr_tile = player->curr_tile->down_neigh;
            layout_->addWidget(player, player->curr_tile->coord_y, player->curr_tile->coord_x);
 //           player->face->setGeometry(player->curr_tile->coord_x, player->curr_tile->coord_y, 90, 90);
 /*           if(player->curr_tile->has_event == true)
              {
              player->curr_tile->has_event = false;
              curr_event = new BgLabel(player->curr_tile->dialog_event, this);
              curr_event->show();
              }*/
          }
      }
    return;
  }

  void mapinterface::slotButtonLeft()
  {
    if(player->curr_tile->l_neigh != 0)
      {
        if(player->curr_tile->l_neigh->walkable == true)
          {
            player->curr_tile = player->curr_tile->l_neigh;
            layout_->addWidget(player, player->curr_tile->coord_y, player->curr_tile->coord_x);
//            player->face->setGeometry(player->curr_tile->coord_x, player->curr_tile->coord_y, 90, 90);
/*            if(player->curr_tile->has_event == true)
              {
              player->curr_tile->has_event = false;
              curr_event = new BgLabel(player->curr_tile->dialog_event, this);
              curr_event->show();
              }*/
          }
      }
    return;
  }

  void mapinterface::slotButtonRight()
  {
    if(player->curr_tile->r_neigh != 0)
      {
        if(player->curr_tile->r_neigh->walkable == true)
          {
            player->curr_tile = player->curr_tile->r_neigh;
            layout_->addWidget(player, player->curr_tile->coord_y, player->curr_tile->coord_x);
//            player->face->setGeometry(player->curr_tile->coord_x, player->curr_tile->coord_y, 90, 90);
/*            if(player->curr_tile->has_event == true)
              {
              player->curr_tile->has_event = false;
              curr_event = new BgLabel(player->curr_tile->dialog_event, this);
              curr_event->show();
              }*/
          }
      }
    return;
  }
