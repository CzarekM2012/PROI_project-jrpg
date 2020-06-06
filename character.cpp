#include "character.h"


character::character():entity(), row_(-1), place_(-1), alive_(false){}

character::character(character *copied):entity(copied), row_(copied->row_), place_(copied->place_), alive_(copied->alive_){}

character::character(const char *name, int *stats, const char *description):entity(name, stats, description), row_(-1), place_(-1), alive_(true){}

void character::set_stat(int value, unsigned int index)
{
    value = value < 0 ? 0 : value;
    entity::set_stat(value, index);
}

void character::set_alive(bool value){alive_ = value;}

void character::set_position(int r, int p)
{
    row_=r;
    place_=p;
}

bool character::alive(){return alive_;}

std::pair<short int, short int> character::get_position(){return std::pair<short int, short int> (row_,place_);}

void character::trigger_statuses()// do NOT create triggering status for stats other than current_hp and current_sp
{
    int change[9]={}, temp[9];
    std::vector<int> statuses_to_remove;
    for(unsigned int i=0; i<triggering_statuses_.size(); i++)
    {
        triggering_statuses_[i].get_stats(temp);
        for(int j=0; j<9; j++){change[j]+=temp[j];}
        if(triggering_statuses_[i].decrease_duration()){statuses_to_remove.push_back(i);}
    }
    int character_state[9];
    get_stats(character_state);
    for(int i=0; i<9; i++)
    {
        int temp = character_state[i]+change[i];
        character_state[i] = temp < 0 ? 0 : temp;
    }
    for(unsigned int i=0; i<statuses_to_remove.size(); i++)
    {
        triggering_statuses_[statuses_to_remove[i]] = triggering_statuses_[triggering_statuses_.size()-(i+1)];
    }
    triggering_statuses_.erase(triggering_statuses_.end()-statuses_to_remove.size()+1, triggering_statuses_.end());
    set_stats(character_state);
    if(get_stat(1) == 0){set_alive(false);}
}

void character::expire_statuses()
{
    int change[9]={}, temp[9];
    std::vector<int> statuses_to_remove;
    for(unsigned int i=0; i<continuous_statuses_.size(); i++)
    {
        if(continuous_statuses_[i].decrease_duration())
        {
            statuses_to_remove.push_back(i);
            continuous_statuses_[i].get_stats(temp);
            for(int j=0; j<9; j++){change[j]+=temp[j];}
        }
    }
    int character_state[9];
    get_stats(character_state);
    for(int i=0; i<9; i++)
    {
        int temp = character_state[i]+change[i];
        character_state[i] = temp < 0 ? 0 : temp;
    }
    for(unsigned int i=0; i<statuses_to_remove.size(); i++)
    {
        continuous_statuses_[statuses_to_remove[i]] = continuous_statuses_[continuous_statuses_.size()-(i+1)];
    }
    continuous_statuses_.erase(continuous_statuses_.end()-statuses_to_remove.size()+1, continuous_statuses_.end());
    set_stats(character_state);
}

void character::add_status_effect(status_effect effect, bool triggering)
{
    if(triggering){triggering_statuses_.push_back(effect);}
    else{continuous_statuses_.push_back(effect);}
}
