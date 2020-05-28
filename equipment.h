#ifndef ECQUIPMENT_H
#define ECQUIPMENT_H
#include "item.h"

class equipment : public item
{
public:
    equipment(),equipment(equipment*), equipment(const char *name, const char*description, short id, short equipment_type, int *stats);
private:
    int stats_modification_array_[9];
    short type_of_equipment_;
};

#endif // ECQUIPMENT_H
