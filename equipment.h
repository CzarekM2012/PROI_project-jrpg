#ifndef ECQUIPMENT_H
#define ECQUIPMENT_H
#include "item.h"

class equipment : public item
{
public:
    equipment(),equipment(equipment*), equipment(const char *name, int *stats, short id, short equipment_type, const char*description="");
    short get_type_of_eq();
private:
    short type_of_equipment_;
};

#endif // ECQUIPMENT_H
