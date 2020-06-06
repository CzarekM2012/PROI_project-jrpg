#include "party.h"

party::party(){item_storage_ = new item_storage;}

party::party(pc *pcs)
{
    int i=0;
    for(int r=0; r<3; r++)
    {
        for (int p=0; p<2; p++)
        {
            if(pcs[i].alive())
            {
                formation_[r][p] = pcs[i];
                formation_[r][p].set_position(r, p);
            }
            i++;
        }
    }
}
party::party(party *party_to_copy)
{
    for(int r=0; r<3; r++)
    {
        for (int p=0; p<2; p++)
        {
            pc* pc_to_copy = party_to_copy->get_pc_address(r, p);
            formation_[r][p] = pc(pc_to_copy);
        }
    }
    item_storage_ = new item_storage(party_to_copy->item_storage_);
}


void party::add_member(pc *added_pc)
{
    for(int r=0; r<3; r++)
    {
        for (int p=0; p<2; p++)
        {
            if(!formation_[r][p].alive())
            {
                formation_[r][p] = *added_pc;
                formation_[r][p].set_position(r, p);
                return;
            }
        }
    }
}

pc *party::get_pc_address(int r, int p)
{
    return &formation_[r][p];
}

void party::swap_members(pc *first_member, pc *second_member)
{
    std::pair<int,int> pos1,pos2;
    pos1 = first_member->get_position();
    pos2 = second_member->get_position();
    pc temporary = *first_member;
    *first_member = *second_member;
    *second_member = temporary;
    first_member->set_position(pos2.first, pos2.second);
    second_member->set_position(pos1.first, pos1.second);
}

item_storage *party::get_item_storage(){return item_storage_;}
