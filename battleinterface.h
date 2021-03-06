#ifndef BATTLEINTERFACE_H
#define BATTLEINTERFACE_H
#include <QPushButton>
#include <QTimer>
#include <QVector>
#include <QSignalMapper>
#include "party_view.h"
#include "enemy_group_view.h"
#include "group_status_panel.h"
#include "switchable_frame.h"
#include "action.h"
#include "equipment_management_interface.h"
#include "skill_choice_panel.h"
#include "change_position_panel.h"
#include "choose_consumable_panel.h"

struct character_descriptor
{
    short int row, position;
    bool pc;
};

class battleinterface: public switchable_frame
{
    Q_OBJECT
public:
    battleinterface(party *travel_party, enemy_group enemy_group, QString background);
    ~battleinterface();
private:
    void create_children();
    void place_children();
    void connect_signals();
    void execute_move();
    void give_control_to_the_player(pc *pc);
    void npc_act(npc *npc);
    bool npc_aoe_heal(npc *acting, int* acting_stats, std::pair<npc*, double>*);
    bool npc_single_target_heal(npc *acting, int* acting_stats, std::pair<npc*, double>*);
    bool npc_aoe_attack(npc *acting, int* acting_stats, std::pair<pc*, double>*);
    void npc_single_target_attack(npc *acting, int* acting_stats, std::pair<pc*, double>*);
    void finalize_action();
    void restart_battle();
    void count_dead();
    void end_turn();
private slots:
    void increase_actions();
    void choose_target(skill *skill);
    void update_target(entity *new_target);
    void take_control_from_the_player();
    void repeat_move();
    void initiate_action();
    void remove_from_layout(switchable_frame*);
signals:
    void defeat();
private:
    party battle_party_;
    enemy_group enemy_group_;
    group_status_panel *party_statuses_, *enemy_group_statuses_;
    party_view *party_view_;
    enemy_group_view *enemy_group_view_;
    QPushButton *attack_, *defence_, *skill_, *item_, *switch_, *return_, *confirm_;
    party *travel_party_;
    QTimer *action_timer_;
    QVector<character_descriptor> action_queue_;
    int queue_index_;
    action *action_ = nullptr;
    skill *normal_attack_ = new skill, *normal_defence_ = new skill("normal defence", "", 6, 5, 5);
};

#endif // BATTLE_INTERFACE_H
