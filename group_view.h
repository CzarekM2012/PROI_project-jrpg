#ifndef GROUP_VIEW_H
#define GROUP_VIEW_H
#include "switchable_frame.h"
#include "party.h"
#include "enemy_group.h"
#include "group_status_panel.h"
#include "character_frame.h"

class group_view: public switchable_frame
{
    Q_OBJECT
public:
    group_view();
    character_frame *get_character_frame(short int r, short int p);
    void set_graphics();
    void prepare_status_panels_highlight(group_status_panel *group_status_panel);
    void reset_states();
private slots:
    void pass_target_info(entity *);
signals:
    void target_info(entity *);
protected:
    character_frame *formation_[2][2]={};
};

#endif // GROUP_VIEW_H
