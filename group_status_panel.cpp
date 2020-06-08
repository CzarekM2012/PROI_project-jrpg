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
    setStyleSheet("QFrame{border-color:black; border-width:2px; border-style:inset; background-color:darkblue}");
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
            if(pc_to_paste_stats->valid()){formation_[r][p]->paste_data(pc_to_paste_stats);}
            else{formation_[r][p]->clear();}
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
            if(npc_to_paste_stats->valid()){formation_[r][p]->paste_data(npc_to_paste_stats);}
            else{formation_[r][p]->clear();}
        }
    }
}
character_status_panel *group_status_panel::get_character_status_panel(short int r, short int p){return formation_[r][p];}

void group_status_panel::swap(std::pair<int, int> pos1, std::pair<int, int> pos2)
{
    QProgressBar *bar1 = formation_[pos1.first][pos1.second]->get_action_bar_(), *bar2=formation_[pos2.first][pos2.second]->get_action_bar_();
    int temp = bar1->value();
    bar1->setValue(bar2->value());
    bar2->setValue(temp);
}

void group_status_panel::reset_action(std::pair<int, int> pos){formation_[pos.first][pos.second]->get_action_bar_()->setValue(0);}
