#ifndef PC_H
#define PC_H
#include "character.h"
#include "npc.h"
#include "equipment.h"
#include "consumable.h"

class pc: public character
{
public:
    pc(), pc(QString name, int *stats_array, skill **skills, equipment **gear_array, QString description=""), pc(pc *pc);
    equipment *get_part_of_equipment(unsigned int);
    void set_part_of_equipment(equipment *, unsigned int);
    bool calculate_stats_after_equip(entity*, int*);
    bool calculate_stats_after_consuming(entity*, int*);
    equipment* equip(equipment*);
    equipment* unequip(int);
    void consume(consumable*);
private:
    equipment *equipment_[7]={};
};

#endif // PC_H
