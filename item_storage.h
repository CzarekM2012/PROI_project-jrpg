#ifndef ITEM_STORAGE_H
#define ITEM_STORAGE_H
#include "equipment.h"
#include "consumable.h"
#include "QPair"
class item_storage
{
public:
    item_storage(), item_storage(item_storage *storage);
    bool add_item(consumable*), add_item(equipment*);
    equipment *get_equipment(int);
    consumable *get_consumable(int);
    int get_equipment_slot(entity *);
    int get_consumable_slot(entity *);
    void set_item(equipment*, unsigned int), set_item(consumable, unsigned int);
private:
    consumable consumables_[20]={};
    equipment *equipment_[80]={};
};

#endif // ITEM_STORAGE_H
