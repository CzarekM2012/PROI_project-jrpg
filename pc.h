#ifndef PC_H
#define PC_H
#include "character.h"
#include "npc.h"
#include "equipment.h"
class pc: public character
{
public:
    pc(), pc(const char *name, int *stats_array, equipment **gear_array, const char *description=""), pc(pc *pc);
    entity *get_part_of_equipment(unsigned int);
    bool calculate_stats_after_equip(entity*, int*);
    equipment* equip(equipment*);
private:
    equipment *equipment_[7]={};
};

#endif // PC_H
