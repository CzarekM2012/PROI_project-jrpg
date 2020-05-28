#include "pc_choice_panel.h"

pc_choice_panel::pc_choice_panel(party *party)
{
    for(int r=0; r<3; r++)
    {
        for (int p=0; p<2; p++)
        {
            /*formation_[r][p] = new target_frame(party->get_pc_address(r, p));
            formation_[r][p]->set_targeting(true);
            formation_[r][p]->set_standard_graphic("-face");*/
        }
    }
}
