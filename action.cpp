#include "action.h"

action::action(){clear();}

void action::clear()
{
    for(int i=0; i<4; i++){targets_[i] = nullptr;}
    acting_ = nullptr;
    skill_ = nullptr;
}

bool action::execute()
{
    int power, base_stat_index = skill_->get_base_stat();
    if(!(acting_->get_counter()==0))
    {
        power = skill_->get_base_power();
    }
    else
    {
        acting_->set_stat(acting_->get_stat(3)-skill_->get_sp_cost(), 3);
        power = skill_->get_base_power() + acting_->get_stat(base_stat_index);
    }
    int affected_stat_index = skill_->get_affected_stat();
    if(skill_->is_attack())
    {
        bool killed = false;
        for(int i=0; i<4; i++)
        {
            if(targets_[i]!=nullptr)
            {
                int temp_power = power;
                if(base_stat_index == 4 || base_stat_index == 6){temp_power -= targets_[i]->get_stat(base_stat_index+1);}
                int current_value = targets_[i]->get_stat(affected_stat_index);
                int result = current_value-temp_power;
                result = result < 0 ? 0 : result;
                targets_[i]->set_stat(result, affected_stat_index);
                if(affected_stat_index != 1 && affected_stat_index != 3)
                {
                    int stats[9]={};
                    stats[affected_stat_index] = temp_power;
                    targets_[i]->add_status_effect(status_effect(stats, 2), false);
                }
                else if(result == 0)
                {
                    targets_[i]->set_alive(false);
                    killed = true;
                }
            }
        }
        if(!(acting_->get_counter()==0))
        {
            acting_->decrease_counter();
            delete skill_;
        }
        return killed;
    }
    for(int i=0; i<4; i++)
    {
        if(targets_[i]!=nullptr)
        {
            int current_value = targets_[i]->get_stat(affected_stat_index);
            int result = current_value+power;
            if(affected_stat_index == 1 || affected_stat_index == 3)
            {
                int max_value = targets_[i]->get_stat(affected_stat_index-1);
                result = result > max_value ? max_value : result;
            }
            targets_[i]->set_stat(result, affected_stat_index);
            if(affected_stat_index!=1)
            {
                int stats[9]={};
                stats[affected_stat_index] = power*(-1);
                targets_[i]->add_status_effect(status_effect(stats, 2), false);
            }
        }
    }
    if(!(acting_->get_counter()==0))
    {
        acting_->decrease_counter();
        delete skill_;
    }
    return false;
}

entity *action::get_acting(){return acting_;}

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
