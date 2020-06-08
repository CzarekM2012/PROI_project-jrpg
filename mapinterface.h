#ifndef MAPINTERFACE_H
#define MAPINTERFACE_H
#include <QPushButton>
#include <vector>
#include "switchable_frame.h"
#include "maptile.h"
#include "playeronmap.h"
#include "tiles_storage.h"
#include "dialoginterface.h"
#include "party.h"
#include "enemy_group.h"
#include "npc.h"
#include "data_processing.h"
#include "equipment.h"


class mapinterface : public switchable_frame
{
    Q_OBJECT
public:
  mapinterface(int tileset, int player_state);
  ~mapinterface();
  tiles_storage *tiles;
  QPushButton *up;
  QPushButton *down;
  QPushButton *left;
  QPushButton *right;
  QPushButton *exit;
  QPushButton *eq;
  playeronmap *player;
  dialoginterface *curr_event;
  party mparty;
  std::vector<npc*> enemies;
  std::vector<consumable*> items;
  std::vector<equipment*> gear;
  std::vector<skill*> skills;
  int map_num;

private slots:
 void slotButtonUp();
 void slotButtonDown();
 void slotButtonLeft();
 void slotButtonRight();
 void slotButtonEq();

private:
  void set_all_neighbors();
  void set_all_events(int tileset);
  int* load_tileset(int *map, std::string path);
  void create_children();
  void place_children();
  void connect_signals();
  void place_player(int player_state);
  void generate_battle();
  void load_enemies(std::vector<npc*> *enemies_vector, std::vector<skill*> *skills_vector);
  void load_items(std::vector<consumable*> *consumables_vector);
  void load_eq(std::vector<equipment*> *equipment_vector);
  void load_party(std::vector<skill *> *skills_vector, std::vector<equipment *> *equipment_vector);

signals:
  void change_map(int m, int p);
  void start_battle(switchable_frame*);

};

#endif // MAPINTERFACE_H
