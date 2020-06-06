#include "pc.h"

pc::pc():character(){}

pc::pc(const char *name, int *stats, equipment **gear_array, const char *description):character(name, stats, description){memcpy(equipment_, gear_array, 7*sizeof (equipment*));}
/*{
    for(int i=0; i<7; i++){equipment_[i] = gear_array[i];}// gear stat changes already in stats_array
}*/

pc::pc(pc *pc):character(pc){memcpy(equipment_, pc->equipment_, 7*sizeof (equipment*));}
/*{
    for(int i=0; i<7; i++){equipment_[i] = pc->equipment_[i];}
}*/

entity *pc::get_part_of_equipment(unsigned int index){return equipment_[index];}

bool pc::calculate_stats_after_equip(entity *equipment, int *target)
{
    int pc_stats[9], ce_stats[9], ne_stats[9], index = equipment->get_type_of_eq();
    get_stats(pc_stats);
    equipment_[index]->get_stats(ce_stats);
    if(equipment!=nullptr){equipment->get_stats(ne_stats);}
    for(int i=0; i<9; i++)
    {
        int new_stat = pc_stats[i]-ce_stats[i]+ne_stats[i];
        if(new_stat < 0)
        {
            return false;
        }
        pc_stats[i] = new_stat;
    }
    memcpy(target, pc_stats, 9*sizeof (int));
    return true;
}

equipment *pc::equip(equipment *to_equip)
{
    int new_stats[9]={};
    int index = to_equip->get_type_of_eq();
    equipment *removed=nullptr;
    if(calculate_stats_after_equip(to_equip, new_stats))
    {
        set_stats(new_stats);
        removed = equipment_[index];
        equipment_[index] = to_equip;
    }
    return removed;
}
