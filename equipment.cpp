#include "equipment.h"

equipment::equipment():item(){}

equipment::equipment(equipment *equipment):item(equipment){type_of_equipment_ = equipment->type_of_equipment_;}

equipment::equipment(const char *name, int *stats, short id, short type, const char *description):item(name, stats, id, description), type_of_equipment_(type){}

short equipment::get_type_of_eq(){return type_of_equipment_;}
