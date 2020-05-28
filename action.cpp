#include "action.h"

action::action(){clear();}

void action::clear()
{
    for(int i=0; i<4; i++){targets_[i] = nullptr;}
    acting_ = nullptr;
    skill_ = nullptr;
}

void action::execute()
{
    int base_stat_index = skill_->get_base_stat();
    int power = skill_->get_base_power() + acting_->get_stat(base_stat_index);
    int affected_stat_index = skill_->get_affected_stat();
    if(skill_->is_attack())
    {
        for(int i=0; i<4; i++)
        {
            if(targets_[i]!=nullptr)
            {
                int temp_power = power;
                if(base_stat_index == 4 || base_stat_index == 6){temp_power -= targets_[i]->get_stat(base_stat_index+1);}
                int current_value = targets_[i]->get_stat(affected_stat_index);
                temp_power = current_value-temp_power < 0 ? current_value : temp_power;
                targets_[i]->set_stat(current_value-temp_power, affected_stat_index);
                if(affected_stat_index!=1)
                {
                    int stats[9]={};
                    stats[affected_stat_index] = temp_power;
                    targets_[i]->add_status_effect(status_effect(stats, 2), false);
                }
            }
        }
        return;
    }
    for(int i=0; i<4; i++)
    {
        if(targets_[i]!=nullptr)
        {
            int current_value = targets_[i]->get_stat(affected_stat_index);
            targets_[i]->set_stat(current_value+power, affected_stat_index);
            if(affected_stat_index!=1)
            {
                int stats[9]={};
                stats[affected_stat_index] = power*(-1);
                targets_[i]->add_status_effect(status_effect(stats, 2), false);
            }
        }
    }
}

void action::set_target(entity *target){targets_[0] = target;}

void action::set_targets(entity *targets_array[4])
{
    targets_[0] = targets_array[0];
    targets_[1] = targets_array[1];
    targets_[2] = targets_array[2];
    targets_[3] = targets_array[3];
}

void action::set_acting(entity *acting){acting_ = acting;}

void action::set_skill(skill *skill){skill_ = skill;}
