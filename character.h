#ifndef CHARACTER_H
#define CHARACTER_H
#include "entity.h"
#include "skill.h"
#include <vector>

class character: public entity
{
public:
    character(), character(const char *name, const char *graphic_file_name, int *stats_array);
    void set_max_hp(int value);
    void set_current_hp(int value);
    void set_max_sp(int value);
    void set_current_sp(int value);
    void set_atk(int value);
    void set_def(int value);
    void set_s_atk(int value);
    void set_s_def(int value);
    void set_initiative(int value);
    void set_stats(int *stats_array), set_stats();
    void set_alive(bool value);
    void set_position(int r, int p);
    int get_max_hp();
    int get_current_hp();
    int get_max_sp();
    int get_current_sp();
    int get_atk();
    int get_def();
    int get_s_atk();
    int get_s_def();
    int get_initiative();
    void get_stats(int *target_array);
    bool alive();
    int get_row();
    int get_place();
    std::pair<short int,short int> get_position();
private:
    int max_hp_, current_hp_, max_sp_, current_sp_, atk_, def_, s_atk_, s_def_, initiative_;
    short int row_, place_;
    bool alive_;
};

#endif // CHARACTER_H
