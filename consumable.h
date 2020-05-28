#ifndef CONSUMABLE_H
#define CONSUMABLE_H
#include "item.h"
#include "skill.h"

class consumable : public item
{
public:
    consumable(), consumable(consumable*), consumable(const char *name, const char *description, const short id, skill *invoked_skill, unsigned int counter);
    void increase_counter(int amount=1);
    bool decrease_counter(int amount=1);
    skill *get_invoked_skill();
private:
    skill *invoked_skill_;
    unsigned int counter_;
};

#endif // CONSUMABLE_H
