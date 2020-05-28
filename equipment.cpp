#include "equipment.h"

equipment::equipment():item(){}

equipment::equipment(equipment *equipment):item(equipment)
{
    type_of_equipment_ = equipment->type_of_equipment_;
    memcpy(stats_modification_array_, equipment->stats_modification_array_, 9*sizeof (int));
}

equipment::equipment(const char *name, const char *description, short id, short type, int *stats):item(name, description, id)
{
    type_of_equipment_ = type;
    memcpy(stats_modification_array_, stats, 9*sizeof (int));
}
