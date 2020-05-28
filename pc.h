#ifndef PC_H
#define PC_H
#include "character.h"
#include "npc.h"
#include "equipment.h"
class pc: public character
{
public:
    pc(), pc(const char *name, const char *description, unsigned int *stats_array, equipment **gear_array);
    pc(character *character), pc(pc *pc), pc(npc *npc);
    equipment *get_part_of_ecquipment(int identifier);
private:
    equipment *equipment_[7]={};
};

#endif // PC_H
