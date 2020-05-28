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
    int id = added_consumable->get_id();
    for(int i=0; i<20; i++)
    {
        if(consumables_[i].get_id() == id)
        {
            consumables_[i].increase_counter();
            return true;
        }
        else if(consumables_[i].get_id() == -1)
        {
           consumables_[i] = consumable(added_consumable);
           return true;
        }
    }
    return false;
}

bool item_storage::add_item(equipment *added_equipmemt)
{
    int id = added_equipmemt->get_id();
    equipment *instance = nullptr;
    for(int i=0; i<80; i++)
    {
        if(equipment_[i]->get_id() == id){instance = equipment_[i];}
        else if(equipment_[i]->get_id() == -1)
        {
            if(instance == nullptr){equipment_[i] = new equipment(added_equipmemt);}
            else{equipment_[i] = instance;}
            return true;
        }
    }
    return false;
}

equipment *item_storage::get_equipment(int index){return equipment_[index];}

consumable *item_storage::get_consumable(int index){return &consumables_[index];}

void item_storage::set_item(equipment *equipment, unsigned int index){equipment_[index] = equipment;}

void item_storage::set_item(consumable consumable, unsigned int index){consumables_[index] = consumable;}
