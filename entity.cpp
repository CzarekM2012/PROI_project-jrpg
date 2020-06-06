#include "entity.h"
#include <iostream>

entity::entity():name_(""), description_(""){}

entity::entity(entity* entity)
{
    name_ = entity->name_;
    description_ = entity->description_;
    memcpy(stats_, entity->stats_, 9*sizeof (int));
}

entity::entity(const char *name, int *stats, const char *description): name_(name), description_(description){memcpy(stats_, stats, 9*sizeof (int));}

entity::~entity(){}

QString entity::get_name(){return name_;}

QString entity::get_description(){return description_;}

void entity::set_name(const char *name){name_ = QString(name);}

void entity::set_name(QString name){name_ = name;}

void entity::set_description(const char *description){description_ = QString(description);}

void entity::set_description(QString description){description_ = description;}

void entity::set_stat(int value, unsigned int index){if(index<9){stats_[index] = value;}}

void entity::set_stats(int stats_array[9]){memcpy(stats_, stats_array, 9*sizeof (int));}

int entity::get_stat(unsigned int index){return index<9 ? stats_[index] : -1;}

void entity::get_stats(int target_array[9]){memcpy(target_array, stats_, 9*sizeof (int));}

void entity::set_alive(bool){}
void entity::set_position(int, int){}
bool entity::alive(){return false;}
std::pair<short int,short int> entity::get_position(){return std::pair<short, short>();}
void entity::trigger_statuses(){}
void entity::expire_statuses(){}
void entity::add_status_effect(status_effect, bool){}
short entity::get_id(){return 0;}
entity *entity::get_part_of_equipment(unsigned int){return nullptr;}
short entity::get_type_of_eq(){return 0;}
int entity::get_counter(){return 0;}
