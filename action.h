#ifndef ACTION_H
#define ACTION_H
#include "character.h"

class action
{
public:
    action();
    void clear();
    void execute();
    void set_target(entity *target);
    void set_targets(entity *targets_array[4]);
    void set_acting(entity *acting);
    void set_skill(skill *skill);
private:
    entity *targets_[4]={}, *acting_;
    skill *skill_; //attack, defense, etc.
};

#endif // ACTION_H
