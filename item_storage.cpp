#include "item_storage.h"

item_storage::item_storage(){}

item_storage::item_storage(item_storage *storage)
{
    memcpy(equipment_, storage->equipment_, 80*sizeof (equipment*));
    for(int i=0; i<20; i++)
    {
        consumables_[i] = storage->consumables_[i];
    }
}

bool item_storage::add_item(consumable *added_consumable)
{
    int index = get_consumable_slot(added_consumable);
    if(index != -1)
    {
        consumables_[index].increase_counter();
        return true;
    }
    index = 0;
    while(consumables_[index].get_id() != -1 && index<20){index++;}
    if(index<20)
    {
        consumables_[index] = consumable(added_consumable);
        return true;
    }
    return false;
}

bool item_storage::add_item(equipment *added_equipmemt)
{
    int id = added_equipmemt->get_id();
    equipment *instance = added_equipmemt;
    for(int i=0; i<80; i++)
    {
        if(equipment_[i] == nullptr)
        {
            equipment_[i] = instance;
            return true;
        }
        else if(equipment_[i]->get_id() == id)
        {
            delete instance;
            instance = equipment_[i];
            id = -1;
        }
    }
    return false;
}

equipment *item_storage::get_equipment(int index){return equipment_[index];}

int item_storage::get_equipment_slot(entity *equipment)
{
    int i=0;
    while(equipment_[i]!=equipment && i<80){i++;}
    if(i<80){return i;}
    return -1;
}

consumable *item_storage::get_consumable(int index){return &consumables_[index];}

int item_storage::get_consumable_slot(entity *consumable)
{
    int id = consumable->get_id(), i=0;
    while(consumables_[i].get_id() != id && i<20){i++;}
    if(i<20){return i;}
    return -1;
}

void item_storage::set_item(equipment* equipment, unsigned int index){equipment_[index] = equipment;}

void item_storage::set_item(consumable consumable, unsigned int index){consumables_[index] = consumable;}
