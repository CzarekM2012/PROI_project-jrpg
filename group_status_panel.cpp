#include "group_status_panel.h"

group_status_panel::group_status_panel()
{
    layout_ = new QGridLayout();
    this->setLayout(layout_);
    for(int r=0; r<2; r++)
    {
        for (int p=0; p<2; p++)
        {
            formation_[r][p] = new character_status_panel();
            layout_->addWidget(formation_[r][p],r,p);
        }
    }
}
group_status_panel::group_status_panel(party *party):group_status_panel(){paste_data(party);}
group_status_panel::group_status_panel(enemy_group *enemy_group):group_status_panel(){paste_data(enemy_group);}

void group_status_panel::paste_data(party *party)
{
    for(int r=0; r<2; r++)
    {
        for (int p=0; p<2; p++)
        {
            pc *pc_to_paste_stats = party->get_pc_address(r, p);
            if(pc_to_paste_stats->alive())
            {
                formation_[r][p]->paste_data(pc_to_paste_stats);
            }
        }
    }
}
void group_status_panel::paste_data(enemy_group *enemy_group)
{
    for(int r=0; r<2; r++)
    {
        for (int p=0; p<2; p++)
        {
            npc *npc_to_paste_stats = enemy_group->get_npc_adress(r, p);
            if(npc_to_paste_stats->alive())
            {
                formation_[r][p]->paste_data(npc_to_paste_stats);
            }
        }
    }
}
character_status_panel *group_status_panel::get_character_status_panel(short int r, short int p){return formation_[r][p];}
