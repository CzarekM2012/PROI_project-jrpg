#include <fstream>
#include "mapinterface.h"
#include "tiles_storage.h"

mapinterface::mapinterface(int tileset, int player_state)
  {
      tiles = new tiles_storage(tileset);
      create_children();
      place_children();
      connect_signals();
      player = new playeronmap(tiles->tiles[player_state], this);
      player->curr_tile->is_curr_tile = true;
      player->setStyleSheet(QString("border-image:url(:/images/face1.png)"));
      tiles->layout_->addWidget(player, player->curr_tile->coord_y, player->curr_tile->coord_x);
  }

  void mapinterface::create_children()
  {
    up = new QPushButton("^");
    up->setMaximumSize(70, 70);
    down = new QPushButton("V");
    down->setMaximumSize(70, 70);
    left = new QPushButton("<-");
    left->setMaximumSize(70, 70);
    right = new QPushButton("->");
    right->setMaximumSize(70, 70);
  }

  void mapinterface::place_children()
  {
      layout_->addWidget(tiles, 0, 0, 7, 10);
      layout_->addWidget(up, 2, 12);
      layout_->addWidget(down, 4, 12);
      layout_->addWidget(left, 3, 11);
      layout_->addWidget(right, 3, 13);
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
            tiles->layout_->addWidget(player, player->curr_tile->coord_y, player->curr_tile->coord_x);
            if(player->curr_tile->has_event == true)
              {
                if(player->curr_tile->new_map>=0)
                emit change_map(player->curr_tile->new_map, player->curr_tile->new_map==1?62:3);
//              player->curr_tile->has_event = false;
//              curr_event = new BgLabel(player->curr_tile->dialog_event, this);
 //             curr_event->show();
              }
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
            tiles->layout_->addWidget(player, player->curr_tile->coord_y, player->curr_tile->coord_x);
            if(player->curr_tile->has_event == true)
              {
                if(player->curr_tile->new_map>=0)
                emit change_map(player->curr_tile->new_map, player->curr_tile->new_map==1?62:3);
//              player->curr_tile->has_event = false;
//              curr_event = new BgLabel(player->curr_tile->dialog_event, this);
//              curr_event->show();
              }
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
            tiles->layout_->addWidget(player, player->curr_tile->coord_y, player->curr_tile->coord_x);
            if(player->curr_tile->has_event == true)
              {
              if(player->curr_tile->new_map>=0)
              emit change_map(player->curr_tile->new_map, player->curr_tile->new_map==1?62:3);
//              player->curr_tile->has_event = false;
 //             curr_event = new BgLabel(player->curr_tile->dialog_event, this);
 //             curr_event->show();
              }
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
            tiles->layout_->addWidget(player, player->curr_tile->coord_y, player->curr_tile->coord_x);
            if(player->curr_tile->has_event == true)
              {
                if(player->curr_tile->new_map>=0)
                emit change_map(player->curr_tile->new_map, player->curr_tile->new_map==1?62:3);
//              player->curr_tile->has_event = false;
//              curr_event = new BgLabel(player->curr_tile->dialog_event, this);
//              curr_event->show();
              }
          }
      }
    return;
  }
