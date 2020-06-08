#ifndef CHARACTER_H
#define CHARACTER_H
#include "entity.h"
#include "skill.h"
#include <vector>

class character: public entity
{
public:
    character(), character(character*), character(QString name, int *stats, skill **skills, QString description="");
    void set_alive(bool value);
    void set_position(int r, int p);
    void set_stat(int value, unsigned int index);
    bool alive();
    bool valid();
    std::pair<short int,short int> get_position();
    void trigger_statuses();
    void expire_statuses();
    skill *get_skill(int);
    void add_status_effect(status_effect status_effect, bool triggering);
    void get_skillset_type(bool*);
    void set_skill(skill *, int);
private:
    skill *skills_[8]={};
    std::vector<status_effect> triggering_statuses_, continuous_statuses_;
    short int row_, place_;
    bool alive_, valid_, skills_types_[4]={false,false,false,false}; //single_target_attack, aoe_attack, single_target_heal, aoe_heal
};

#endif // CHARACTER_H
