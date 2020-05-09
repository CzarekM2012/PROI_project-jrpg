#ifndef ACTION_H
#define ACTION_H
#include "character.h"

class action
{
public:
    action();
    void clear();
    void execute();
    void set_target(character *target);
    void set_acting(character *acting);
    void set_type(int value);
private:
    character *target_, *acting_;
    int type_; //attack, defense, etc.
};

#endif // ACTION_H
