#ifndef EQUIPMENT_H
#define EQUIPMENT_H
#include "item.h"

class equipment : public item
{
public:
    equipment(),equipment(equipment*), equipment(QString name, int *stats, short id, short equipment_type, QString description="");
    short get_type_of_eq();
private:
    short type_of_equipment_;
};

#endif // EQUIPMENT_H
