#ifndef GROUP_VIEW_H
#define GROUP_VIEW_H
#include <QFrame>
#include <QGridLayout>
#include "party.h"
#include "enemy_group.h"
#include "group_status_panel.h"
#include "character_frame.h"

class group_view: public QFrame
{
public:
    group_view();
    character_frame *get_character_frame(short int r, short int p);
    void place_frame(character_frame *frame, int row, int column, int rowspan, int columnspan);
    void set_graphic(character_frame *frame, QString *new_graphic_file_name);
    void set_graphics(party *party);
    void set_graphics(enemy_group *enemy_group);
    void prepare_status_panels_highlight(group_status_panel *group_status_panel);
    void prepare_action_target_acquisition();
    void set_party(bool is_party);
private:
    character_frame *formation_[2][2];
    QGridLayout *layout_;
    bool party_;
};

#endif // GROUP_VIEW_H
