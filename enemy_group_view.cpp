#include "enemy_group_view.h"

enemy_group_view::enemy_group_view(switchable_frame *parent, enemy_group *enemy_group):group_view(parent)
{
    int frames_coordinates[2][2][2]={{{5,5},{4,0}},{{1,9},{0,4}}};
    for(int r=0; r<2; r++)
    {
        for(int p=0; p<2; p++)
        {
            character_frame *frame = get_character_frame(r, p);
            layout_->addWidget(frame, frames_coordinates[r][p][0], frames_coordinates[r][p][1], 4, 3);
            npc *npc = enemy_group->get_npc_adress(r, p);
            frame->set_represented_object(npc);
            frame->set_standard_graphic();
            if(npc->alive()){frame->set_state(1);}
        }
    }
}
