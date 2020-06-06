#ifndef CHARACTER_H
#define CHARACTER_H
#include "entity.h"
#include "skill.h"
#include <vector>

class character: public entity
{
public:
    character(), character(character*), character(const char *name, int *stats, const char *description);
    void set_alive(bool value);
    void set_position(int r, int p);
    void set_stat(int value, unsigned int index);
    bool alive();
    std::pair<short int,short int> get_position();
    void trigger_statuses();
    void expire_statuses();
    void add_status_effect(status_effect status_effect, bool triggering);
    //entity * get_part_of_equipment(unsigned int);
private:
    short int row_, place_;
    skill *skills[8]={};
    std::vector<status_effect> triggering_statuses_, continuous_statuses_;
    bool alive_;
};

#endif // CHARACTER_H
