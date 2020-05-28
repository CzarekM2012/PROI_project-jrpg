#include "equipment_management_interface.h"

ecquipment_management_interface::ecquipment_management_interface(){}

ecquipment_management_interface::ecquipment_management_interface(party *party):switchable_frame()
{
    party_ = party;
    int r=0, p=0;
    pc *temp = nullptr;
    while(temp == nullptr && r!=4)
    {
        temp = party_->get_pc_address(r, p++);
        temp = temp->get_name() != QString("") ? temp : nullptr;
        if(p == 2)
        {
            p = 0;
            r++;
        }
    }
    pc_display_ = new pc_ecquipment_display(temp);// player will not be able to set off this function before he gets a party with at least 1 member
    layout_->addWidget(pc_display_, 0, 0, 4, 3);
}

void ecquipment_management_interface::display_pc_ecquipment(pc *pc)
{

}
