#include "entity.h"
#include <iostream>

entity::entity():name_(""), description_(""){}

entity::entity(entity* entity)
{
    name_ = entity->name_;
    description_ = entity->description_;
}

entity::entity(const char *name, const char *description): name_(name), description_(description){}

entity::~entity(){}

QString entity::get_name(){return name_;}

QString entity::get_description(){return description_;}


void entity::set_name(const char *name)
{
    name_ = QString(name);
}

void entity::set_name(QString name)
{
    name_ = name;
}

void entity::set_description(const char *description)
{
    description_ = QString(description);
}
void entity::set_description(QString description)
{
    description_ = description;
}

void entity::set_max_hp(unsigned int){}
void entity::set_current_hp(unsigned int){}
void entity::set_max_sp(unsigned int){}
void entity::set_current_sp(unsigned int){}
void entity::set_atk(unsigned int){}
void entity::set_def(unsigned int){}
void entity::set_s_atk(unsigned int){}
void entity::set_s_def(unsigned int){}
void entity::set_initiative(unsigned int){}
void entity::set_stats(unsigned int *){}
void entity::set_stat(unsigned int, unsigned int){}
void entity::set_stats(){}
void entity::set_alive(bool){}
void entity::set_position(int, int){}
unsigned int entity::get_max_hp(){return 0;}
unsigned int entity::get_current_hp(){return 0;}
unsigned int entity::get_max_sp(){return  0;}
unsigned int entity::get_current_sp(){return 0;}
unsigned int entity::get_atk(){return 0;}
unsigned int entity::get_def(){return  0;}
unsigned int entity::get_s_atk(){return 0;}
unsigned int entity::get_s_def(){return 0;}
unsigned int entity::get_initiative(){return 0;}
unsigned int entity::get_stat(unsigned int){return 0;}
void entity::get_stats(unsigned int *){}
bool entity::alive(){return false;}
int entity::get_row(){return 0;}
int entity::get_place(){return 0;}
std::pair<short int,short int> entity::get_position(){return std::pair<short, short>();}
void entity::trigger_statuses(){}
void entity::expire_statuses(){}
void entity::add_status_effect(status_effect, bool){}
short entity::get_id(){return 0;}
