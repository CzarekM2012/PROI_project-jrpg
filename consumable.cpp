#include "consumable.h"

consumable::consumable():item(){}

consumable::consumable(consumable *consumable):item(consumable)
{
    invoked_skill_ = consumable->invoked_skill_;
    counter_ = consumable->counter_;
}

consumable::consumable(const char *name, const char *description, const short id, skill *invoked_skill, unsigned int counter):item(name, description, id), counter_(counter){invoked_skill_ = invoked_skill;}

void consumable::increase_counter(int amount){counter_+=amount;}

bool consumable::decrease_counter(int amount)
{
    counter_= counter_-amount<0 ? 0 : counter_-amount;
    return counter_=0;
}

skill *consumable::get_invoked_skill(){return invoked_skill_;}
