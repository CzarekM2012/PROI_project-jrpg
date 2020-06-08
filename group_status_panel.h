#ifndef GROUP_STATUS_PANEL_H
#define GROUP_STATUS_PANEL_H
#include <QWidget>
#include "character_status_panel.h"
#include "party.h"
#include "enemy_group.h"
class group_status_panel: public QFrame
{
public:
    group_status_panel(), group_status_panel(party *party), group_status_panel(enemy_group *enemy_group);
    character_status_panel *get_character_status_panel(short int r,short int p);
    void paste_data(party *party), paste_data(enemy_group *enemy_group);
    void swap(std::pair<int,int>,std::pair<int,int>);
    void reset_action(std::pair<int,int>);
private:
    character_status_panel *formation_[2][2];
    QGridLayout *layout_;
};

#endif // GROUP_STATUS_PANEL_H
