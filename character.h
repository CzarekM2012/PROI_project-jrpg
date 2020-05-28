#ifndef CHARACTER_H
#define CHARACTER_H
#include "entity.h"
#include "skill.h"
#include <vector>

class character: public entity
{
public:
    character(), character(character*), character(const char *name, const char *description, unsigned int *stats_array);
    void set_max_hp(unsigned int value);
    void set_current_hp(unsigned int value);
    void set_max_sp(unsigned int value);
    void set_current_sp(unsigned int value);
    void set_atk(unsigned int value);
    void set_def(unsigned int value);
    void set_s_atk(unsigned int value);
    void set_s_def(unsigned int value);
    void set_initiative(unsigned int value);
    void set_stat(unsigned int value, unsigned int index);
    void set_stats(unsigned int *stats_array), set_stats();
    void set_alive(bool value);
    void set_position(int r, int p);
    unsigned int get_max_hp();
    unsigned int get_current_hp();
    unsigned int get_max_sp();
    unsigned int get_current_sp();
    unsigned int get_atk();
    unsigned int get_def();
    unsigned int get_s_atk();
    unsigned int get_s_def();
    unsigned int get_initiative();
    unsigned int get_stat(unsigned int index);
    void get_stats(unsigned int *target_array);
    bool alive();
    int get_row();
    int get_place();
    std::pair<short int,short int> get_position();
    void trigger_statuses();
    void expire_statuses();
    void add_status_effect(status_effect status_effect, bool triggering);
private:
    unsigned int max_hp_, current_hp_, max_sp_, current_sp_, atk_, def_, s_atk_, s_def_, initiative_;
    short int row_, place_;
    skill *skills[8]={};
    std::vector<status_effect> triggering_statuses_, continuous_statuses_;
    bool alive_;
};

#endif // CHARACTER_H
