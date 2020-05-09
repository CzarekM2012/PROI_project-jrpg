#include "character.h"


character::character():entity()
{
    set_stats();
    alive_ = false;
    row_=-1;
    place_=-1;
}
character::character(const char *name, const char *graphic_file_name, int *stats_array):entity(name, graphic_file_name)
{
    set_stats(stats_array);
    alive_ = true;
    row_=-1;
    place_=-1;
}

void character::set_max_hp(int value){max_hp_ = value;}
void character::set_current_hp(int value){current_hp_ = value;}
void character::set_max_sp(int value){max_sp_ = value;}
void character::set_current_sp(int value){current_sp_ = value;}
void character::set_atk(int value){atk_ = value;}
void character::set_def(int value){def_ = value;}
void character::set_s_atk(int value){s_atk_ = value;}
void character::set_s_def(int value){s_def_ = value;}
void character::set_initiative(int value){initiative_ = value;}
void character::set_stats(int *stats_array)
{
    max_hp_ = stats_array[0];
    current_hp_ = stats_array[1];
    max_sp_ = stats_array[2];
    current_sp_ = stats_array[3];
    atk_ = stats_array[4];
    def_ = stats_array[5];
    s_atk_ = stats_array[6];
    s_def_ = stats_array[7];
    initiative_ = stats_array[8];
}
void character::set_stats()
{
    set_max_hp(0);
    set_current_hp(0);
    set_max_sp(0);
    set_current_sp(0);
    set_atk(0);
    set_def(0);
    set_s_atk(0);
    set_s_def(0);
    set_initiative(0);
}
void character::set_alive(bool value){alive_ = value;}
void character::set_position(int r, int p)
{
    row_=r;
    place_=p;
}
int character::get_max_hp(){return max_hp_;}
int character::get_current_hp(){return current_hp_;}
int character::get_max_sp(){return max_sp_;}
int character::get_current_sp(){return current_sp_;}
int character::get_atk(){return atk_;}
int character::get_def(){return def_;}
int character::get_s_atk(){return s_atk_;}
int character::get_s_def(){return s_def_;}
int character::get_initiative(){return initiative_;}
void character::get_stats(int *target_array)
{
    target_array[0] = get_max_hp();
    target_array[1] = get_current_hp();
    target_array[2] = get_max_sp();
    target_array[3] = get_current_sp();
    target_array[4] = get_atk();
    target_array[5] = get_def();
    target_array[6] = get_s_atk();
    target_array[7] = get_s_def();
    target_array[8] = get_initiative();
}
bool character::alive(){return alive_;}

int character::get_row(){return row_;}

int character::get_place(){return place_;}

std::pair<short int, short int> character::get_position(){return std::pair<short int, short int> (row_,place_);}
