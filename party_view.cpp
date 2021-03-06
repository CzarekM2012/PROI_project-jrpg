#include "party_view.h"

party_view::party_view(party *party) : group_view()
{
    int frames_coordinates[2][2][2]={{{0,4}, {1,9}}, {{4,0}, {5,5}}};
    for(int r=0; r<2; r++)
    {
        for(int p=0; p<2; p++)
        {
            character_frame *frame = formation_[r][p];
            layout_->addWidget(frame, frames_coordinates[r][p][0], frames_coordinates[r][p][1], 4, 3);
            pc *pc = party->get_pc_address(r, p);
            frame->set_represented_object(pc);
            frame->set_standard_graphic();
            if(pc->valid()){frame->set_state(1);}
        }
    }
}
