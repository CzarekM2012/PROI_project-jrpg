#include <fstream>
#include <stdlib.h>
#include "mapinterface.h"
#include "tiles_storage.h"
#include "battleinterface.h"
#include "switchable_frame.h"
#include "data_processing.h"
#include "npc.h"

mapinterface::mapinterface(int tileset, int player_state)
  {
      tiles = new tiles_storage(tileset);
      map_num = tileset;
      load_enemies(&enemies, &skills);
      load_items(&items);
      load_eq(&gear);
      load_party(&skills, &gear);

      create_children();
      place_children();
      connect_signals();
      place_player(player_state);
  }

mapinterface::~mapinterface()
{
    for(unsigned int i=0; i<gear.size(); i++){delete gear[i];}
    for(unsigned int i=0; i<items.size(); i++){delete items[i];}
    for(unsigned int i=0; i<enemies.size(); i++){delete enemies[i];}
    for(unsigned int i=0; i<skills.size(); i++){delete skills[i];}
}

void mapinterface::load_enemies(std::vector<npc*> *enemies_vector, std::vector<skill*> *skills_vector)
{
  if(map_num == 0)
    {
      read_npc("green slime", enemies_vector, skills_vector);
      read_npc("red slime", enemies_vector, skills_vector);
      read_npc("purple slime", enemies_vector, skills_vector);
      read_npc("spider", enemies_vector, skills_vector);
    }
  else if(map_num == 1)
    {
      read_npc("scorpio", enemies_vector, skills_vector);
      read_npc("mummy light", enemies_vector, skills_vector);
      read_npc("mummy dark", enemies_vector, skills_vector);
    }
  else
    {
      read_npc("ghost", enemies_vector, skills_vector);
      read_npc("mimic", enemies_vector, skills_vector);
      read_npc("knight", enemies_vector, skills_vector);
    }
}

void mapinterface::load_items(std::vector<consumable*> *consumables_vector)
{
  read_consumable("bomba", consumables_vector);
  read_consumable("apteczka", consumables_vector);
  read_consumable("icetea", consumables_vector);
}

void mapinterface::load_eq(std::vector<equipment *> *equipment_vector)
{
    read_equipment("czapeczka", equipment_vector);
    read_equipment("bluza", equipment_vector);
    read_equipment("sweterek", equipment_vector);
    read_equipment("adidaski", equipment_vector);
    read_equipment("patyk", equipment_vector);
    read_equipment("siekiera", equipment_vector);
}

  void mapinterface::load_party(std::vector<skill*> *skills_vector, std::vector<equipment*> *equipment_vector)
  {
    pc arr[6];
    arr[0] = read_pc("oskar", skills_vector, equipment_vector);
    arr[1] = read_pc("sara", skills_vector, equipment_vector);
    arr[2] = read_pc("tina", skills_vector, equipment_vector);
    arr[3] = read_pc("jacek", skills_vector, equipment_vector);
    arr[4] = read_pc("lena", skills_vector, equipment_vector);
    arr[5] = read_pc("alek", skills_vector, equipment_vector);
    mparty = party(arr);
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
    eq = new QPushButton("Ekwipunek");
    eq->setMaximumSize(70, 70);
    exit = new QPushButton("X");
    exit->setMaximumSize(70, 70);
  }

  void mapinterface::generate_battle()
  {
    //na podstawie przeciwników dostepnych w wektorze enemies
    //party *bparty, enemy_group enemies, QString bg
    //party *bparty = parent->tparty;
    npc arr[4];
    int number = rand() % 4;
    int i =0;
    for(number; number>=0; number--)
    {
    arr[i] = enemies[rand() % enemies.size()];
    i++;
    }
    enemy_group enms = enemy_group(arr);
    QString bg = ":/images/path.png";
    battleinterface *battle = new battleinterface(&mparty, enms, bg);
    emit start_battle(battle);
  }

  void mapinterface::place_children()
  {
      layout_->addWidget(tiles, 0, 0, 7, 10);
      layout_->addWidget(up, 2, 12);
      layout_->addWidget(down, 4, 12);
      layout_->addWidget(left, 3, 11);
      layout_->addWidget(right, 3, 13);
      layout_->addWidget(eq, 6, 12);
      layout_->addWidget(exit, 0, 13);
  }

  void mapinterface::connect_signals()
  {
    connect(up, SIGNAL (clicked(bool)), this, SLOT (slotButtonUp()));
    connect(down, SIGNAL (clicked(bool)), this, SLOT (slotButtonDown()));
    connect(left, SIGNAL (clicked(bool)), this, SLOT (slotButtonLeft()));
    connect(right, SIGNAL (clicked(bool)), this, SLOT (slotButtonRight()));
    connect(eq, SIGNAL (clicked(bool)), this, SLOT (slotButtonEq()));
    connect(exit, &QPushButton::clicked, this, [this](){emit close_signal(this);});
    return;
  }

  void mapinterface::place_player(int player_state)
  {
    player = new playeronmap(tiles->tiles[player_state], this);
    player->curr_tile->is_curr_tile = true;
    player->int_curr_tile = player_state;
    player->setStyleSheet(QString("border-image:url(:/images/face1.png)"));
    tiles->layout_->addWidget(player, player->curr_tile->coord_y, player->curr_tile->coord_x);
  }

  void mapinterface::slotButtonEq()
  {
    equipment_management_interface *equipment = new equipment_management_interface(&mparty);
    equipment->setParent(this);
    equipment->setGeometry(this->width()/7, this->height()/7, this->width()*6/7, this->height()*6/7);
    equipment->show();
  }

  void mapinterface::slotButtonUp()
  {
    if(player->curr_tile->up_neigh != 0)
      {
        if(player->curr_tile->up_neigh->walkable == true)
          {
            player->curr_tile = player->curr_tile->up_neigh;
            player->int_curr_tile -= 10;
            tiles->layout_->addWidget(player, player->curr_tile->coord_y, player->curr_tile->coord_x);
            if(player->curr_tile->has_event == true)
              {
                player->curr_tile->has_event = false;
                if(player->curr_tile->d_event >= 0)
                  {
                  curr_event = new dialoginterface(player->curr_tile->d_event);
                  layout_->addWidget(curr_event, 0, 0, 8, 15);
                  }
                if(player->curr_tile->new_map>=0)
                  emit change_map(player->curr_tile->new_map, player->curr_tile->new_map==1?62:3);
              }
            else
              {
                int number = rand() % 12;
                if(number%4 == 0)
                  generate_battle();
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
            player->int_curr_tile += 10;
            tiles->layout_->addWidget(player, player->curr_tile->coord_y, player->curr_tile->coord_x);
            if(player->curr_tile->has_event == true)
              {
                player->curr_tile->has_event = false;
                if(player->curr_tile->d_event >= 0)
                  {
                  curr_event = new dialoginterface(player->curr_tile->d_event);
                  layout_->addWidget(curr_event, 0, 0, 8, 15);
                  }
              if(player->curr_tile->new_map>=0)
                emit change_map(player->curr_tile->new_map, player->curr_tile->new_map==2?9:3);
              }
            else
              {
                int number = rand() % 12;
                if(number%4 == 0)
                  generate_battle();
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
            player->int_curr_tile -= 1;
            tiles->layout_->addWidget(player, player->curr_tile->coord_y, player->curr_tile->coord_x);
            if(player->curr_tile->has_event == true)
              {
                player->curr_tile->has_event = false;
              if(player->curr_tile->d_event >= 0)
                {
                curr_event = new dialoginterface(player->curr_tile->d_event);
                layout_->addWidget(curr_event, 0, 0, 8, 15);
                }
              if(player->curr_tile->new_map>=0)
                emit change_map(player->curr_tile->new_map, player->curr_tile->new_map==1?62:3);
              }
            else
              {
                int number = rand() % 12;
                if(number%4 == 0)
                  generate_battle();
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
            player->int_curr_tile += 1;
            tiles->layout_->addWidget(player, player->curr_tile->coord_y, player->curr_tile->coord_x);
            if(player->curr_tile->has_event == true)
              {
                player->curr_tile->has_event = false;
                if(player->curr_tile->d_event >= 0)
                  {
                  curr_event = new dialoginterface(player->curr_tile->d_event);
                  layout_->addWidget(curr_event, 0, 0, 8, 15);
                  }
              if(player->curr_tile->new_map>=0)
                emit change_map(player->curr_tile->new_map, player->curr_tile->new_map==1?68:3);
              }
            else
              {
                int number = rand() % 12;
                if(number%4 == 0)
                  generate_battle();
              }
          }
      }
    return;
  }
