#include "party_display.h"

party_display::party_display(party *party)
{
    party_=party;
    for(short r=0; r<3; r++)
    {
        for(short p=0; p<2; p++)
        {
            formation_[r][p] = new character_frame(party->get_pc_address(r, p), 6);
            formation_[r][p]->set_standard_graphic("-face");
            layout_->addWidget(formation_[r][p], p ,2-r);
            connect(formation_[r][p], SIGNAL(target_acquired(entity *)), this, SLOT(pass_choice(entity*)));
            connect(this, SIGNAL(choosen_character(entity*)), formation_[r][p], SLOT(is_target(entity*)));
        }
    }
}

void party_display::update()
{
    for(short r=0; r<3; r++)
    {
        for(short p=0; p<2; p++)
        {
            formation_[r][p]->set_represented_object(party_->get_pc_address(r, p));
            formation_[r][p]->set_state(6);
            formation_[r][p]->set_standard_graphic("-face");
        }
    }
}

void party_display::pass_choice(entity* entity){emit choosen_character(entity);}
