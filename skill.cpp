#include "skill.h"

skill::skill(QString name, QString description, short type, short base, short affected, int power, int cost) : name_(name), description_(description), base_power_(power), spcost_(cost), base_stat_(base), affected_stat_(affected), type_(type){}

QString skill::get_name(){return name_;}

QString skill::get_description(){return description_;}

int skill::get_base_power(){return base_power_;}

int skill::get_sp_cost(){return spcost_;}

short skill::get_base_stat(){return base_stat_;}

short skill::get_affected_stat(){return affected_stat_;}

bool skill::is_attack(){return(type_>0 && type_<5);}

bool skill::aoe(){return(type_==2 || type_==7);}

bool skill::is_self_targettable(){return type_==5;}

bool skill::revive(){return type_==8;}

bool skill::operator==(skill skill)
{
    return (base_power_==skill.base_power_ && spcost_==skill.spcost_ && base_stat_==skill.base_stat_ && affected_stat_==skill.affected_stat_ && type_==skill.type_);
}
