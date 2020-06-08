#ifndef SKILL_H
#define SKILL_H
#include <QString>

class skill
{
public:
    skill(QString name="normal attack", QString description="", short type=1, short base=4, short affected=1, int power=0, int cost=0);
    QString get_name();
    QString get_description();
    int get_base_power();
    int get_sp_cost();
    short get_base_stat();
    short get_affected_stat();
    bool is_attack();
    bool aoe();
    bool is_self_targettable();
    bool revive();
    bool operator==(skill skill);
private:
    QString name_, description_;
    int base_power_, spcost_;
    short base_stat_, affected_stat_;
    short type_;//single_target_attack, aoe_attack, single_target_self-targettable_support, single_target_non-self-targettable_support, aoe_support, single_target_revive
                //         1                2                       5                                           6                           7                  8
};

#endif // SKILL_H
