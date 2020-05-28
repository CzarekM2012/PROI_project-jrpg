#include "pc.h"

pc::pc():character(){}

pc::pc(const char *name, const char *description, unsigned int *stats_array, equipment **gear_array):character(name, description, stats_array)
{
    for(int i=0; i<7; i++)
    {
        equipment_[i] = gear_array[i];// gear stat changes already in stats_array
    }
}

pc::pc(character *copied_character):character(copied_character)
{
    delete copied_character;
}

pc::pc(pc *pc):character(pc)
{
    for(int i=0; i<7; i++){equipment_[i] = pc->equipment_[i];}
}

pc::pc(npc *npc):character(npc)
{
    delete npc;
}

equipment *pc::get_part_of_ecquipment(int identifier){return equipment_[identifier];}
