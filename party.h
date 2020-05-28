#ifndef PARTY_H
#define PARTY_H
#include "pc.h"
#include "item_storage.h"

class party
{
public:
    party(), party(pc *pcs), party(party *party_to_copy);
    void add_member(pc *added_pc);
    pc *get_pc_address(int r, int p);
    void swap_members(pc *first_member, pc *second_member);
    item_storage *get_item_storage();
private:
    void rewrite_from_pcs_and_delete_copies();
    pc formation_[3][2]={}; //frontline - backline - reserve
    item_storage *item_storage_;
    skill *available_skills[48]={};
};

#endif // PARTY_H
