#ifndef CONSUMABLE_H
#define CONSUMABLE_H
#include "item.h"
#include "skill.h"

class consumable : public item
{
public:
    consumable(), consumable(consumable*), consumable(QString name, int *stats, const short id, bool battle_item, unsigned int counter=1, QString description="");
    int get_counter();
    void increase_counter(int amount=1);
    void decrease_counter(int amount=1);
    bool battle_item();
private:
    int counter_;
    bool battle_item_;
};

#endif // CONSUMABLE_H
