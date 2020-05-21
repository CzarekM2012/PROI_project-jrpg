#include "maplabel.h"
#include "maptile.h"
#include "playeronmap.h"
#include "bglabel.h"
#include <QPushButton>
#include <QLabel>

MapLabel::MapLabel(int tileset, QWidget *parent) : QWidget(parent)
{
  this->setGeometry(0, 0, 1300, 650);
  init_tiles(tileset);
  set_all_neighbors();
  player = new PlayerOnMap(tiles[27], this);

  up = new QPushButton("^", this);
  down = new QPushButton("V", this);
  left = new QPushButton("<-", this);
  right = new QPushButton("->", this);

  up->setGeometry(880, 350, 50, 50);
  down->setGeometry(880, 450, 50, 50);
  left->setGeometry(830, 400, 50, 50);
  right->setGeometry(930, 400, 50, 50);

  connect(up, SIGNAL (clicked(bool)), this, SLOT (slotButtonUp()));
  connect(down, SIGNAL (clicked(bool)), this, SLOT (slotButtonDown()));
  connect(left, SIGNAL (clicked(bool)), this, SLOT (slotButtonLeft()));
  connect(right, SIGNAL (clicked(bool)), this, SLOT (slotButtonRight()));

  curr_event = nullptr;

  tiles[51]->has_event = true;
  tiles[51]->dialog_event = 1;
  tiles[57]->has_event = true;
  tiles[57]->dialog_event = 2;

}

void MapLabel::init_tiles(int tileset)
{
//int tileset: 0=plains, 1=sand forest, 2=ruins
  QString tf = ":/images/";
  std::vector<QString> all_tiles = {":/images/grass_bg.png", ":/images/trees_bg.png", ":/images/path_dirt_bg.png",
                                    ":/images/stone_bg.png", ":/images/water_corner_bg.png", ":/images/water_edge_bg.png",
                                    ":/images/water_edge_vert_bg.png",};
  bool walkable[7] = {true, false, true, true, false, false, false};
  int tileset0[70] = {1, 1, 1, 2, 1, 0, 1, 1, 1, 1,
                      1, 1, 0, 2, 0, 0, 0, 1, 1, 1,
                      1, 0, 0, 2, 0, 0, 1, 0, 1, 0,
                      1, 0, 2, 2, 0, 1, 1, 0, 0, 3,
                      0, 0, 2, 0, 1, 1, 0, 3, 0, 0,
                      0, 2, 2, 0, 1, 0, 0, 0, 0, 1,
                      0, 2, 0, 3, 0, 0, 4, 6, 6, 6};

if(tileset == 0)
  {
    MapTile* new_tile;
    int pctr = 0;
    for(int j=10; j<500; j+=80)
      {
        for(int i=10; i<750; i+=80)
        {
        new_tile = new MapTile(i, j, all_tiles[tileset0[pctr]], this, walkable[tileset0[pctr]]);
        pctr++;
        tiles.push_back(new_tile);
        }
      }
  }
  return;

}

void MapLabel::set_all_neighbors()
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

void MapLabel::slotButtonUp()
{
  if(player->curr_tile->up_neigh != 0)
    {
      if(player->curr_tile->up_neigh->walkable == true)
        {
          player->curr_tile = player->curr_tile->up_neigh;
          player->face->setGeometry(player->curr_tile->coord_x, player->curr_tile->coord_y, 80, 80);
          if(player->curr_tile->has_event == true)
            {
            player->curr_tile->has_event = false;
            curr_event = new BgLabel(player->curr_tile->dialog_event, this);
            curr_event->show();
            }
        }
    }
  return;
}

void MapLabel::slotButtonDown()
{
  if(player->curr_tile->down_neigh != 0)
    {
      if(player->curr_tile->down_neigh->walkable == true)
        {
          player->curr_tile = player->curr_tile->down_neigh;
          player->face->setGeometry(player->curr_tile->coord_x, player->curr_tile->coord_y, 80, 80);
          if(player->curr_tile->has_event == true)
            {
            player->curr_tile->has_event = false;
            curr_event = new BgLabel(player->curr_tile->dialog_event, this);
            curr_event->show();
            }
        }
    }
  return;
}

void MapLabel::slotButtonLeft()
{
  if(player->curr_tile->l_neigh != 0)
    {
      if(player->curr_tile->l_neigh->walkable == true)
        {
          player->curr_tile = player->curr_tile->l_neigh;
          player->face->setGeometry(player->curr_tile->coord_x, player->curr_tile->coord_y, 80, 80);
          if(player->curr_tile->has_event == true)
            {
            player->curr_tile->has_event = false;
            curr_event = new BgLabel(player->curr_tile->dialog_event, this);
            curr_event->show();
            }
        }
    }
  return;
}

void MapLabel::slotButtonRight()
{
  if(player->curr_tile->r_neigh != 0)
    {
      if(player->curr_tile->r_neigh->walkable == true)
        {
          player->curr_tile = player->curr_tile->r_neigh;
          player->face->setGeometry(player->curr_tile->coord_x, player->curr_tile->coord_y, 80, 80);
          if(player->curr_tile->has_event == true)
            {
            player->curr_tile->has_event = false;
            curr_event = new BgLabel(player->curr_tile->dialog_event, this);
            curr_event->show();
            }
        }
    }
  return;
}
