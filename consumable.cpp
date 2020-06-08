#include "consumable.h"

consumable::consumable():item(), counter_(0){}

consumable::consumable(consumable *consumable):item(consumable), counter_(consumable->counter_), battle_item_(consumable->battle_item_){}

consumable::consumable(QString name, int *stats, const short id, bool battle_item, unsigned int counter, QString description):item(name, stats, id, description), counter_(counter), battle_item_(battle_item){}

int consumable::get_counter(){return counter_;}

void consumable::increase_counter(int amount){counter_+=amount;}

void consumable::decrease_counter(int amount)
{
    counter_= counter_-amount<0 ? 0 : counter_-amount;
    if(counter_ == 0){*this = consumable();}
}

bool consumable::battle_item(){return battle_item_;}
