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

struct character_descriptor
{
    short int row, position;
    bool pc;
};

class battleinterface: public switchable_frame
{
    Q_OBJECT
public:
    /*battleinterface(QMainWindow *parent),*/ battleinterface(party *travel_party, enemy_group enemy_group);
private:
    void create_children();
    void place_children();
    void connect_signals();
    void execute_move();
    void give_control_to_the_player(pc *pc);
    void finalize_action();
    void npc_act(npc *npc);
    void restart_battle();
private slots:
    void increase_actions();
    void choose_target(int group);
    void update_target(character *new_target);
    void repeat_move();
    void take_control_from_the_player();


private:
    party battle_party_;
    enemy_group enemy_group_;
    group_status_panel *party_statuses_, *enemy_group_statuses_;
    party_view *party_view_;
    enemy_group_view *enemy_group_view_;
    QPushButton *attack_, *defense_, *skill_, *return_, *confirm_;
    party *travel_party_;
    QTimer *action_timer_;
    QVector<character_descriptor> action_queue_;
    int queue_index_;
    action *action_ = nullptr;
    QSignalMapper *button_mapper_ = nullptr;
};

#endif // BATTLE_INTERFACE_H
