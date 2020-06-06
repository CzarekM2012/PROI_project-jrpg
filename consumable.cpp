#include "consumable.h"

consumable::consumable():item(){}

consumable::consumable(consumable *consumable):item(consumable){counter_ = consumable->counter_;}

consumable::consumable(const char *name, int *stats, const short id, bool battle_item, unsigned int counter, const char *description):item(name, stats, id, description), counter_(counter), battle_item_(battle_item){}

int consumable::get_counter(){return counter_;}

void consumable::increase_counter(int amount){counter_+=amount;}

bool consumable::decrease_counter(int amount)
{
    counter_= counter_-amount<0 ? 0 : counter_-amount;
    return counter_==0;
}

bool consumable::battle_item(){return battle_item_;}
