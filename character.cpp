#include "character.h"


character::character():entity()
{
    set_stats();
    alive_ = false;
    row_=-1;
    place_=-1;
}

character::character(character *copied):entity(copied)
{
    unsigned int stats[9];
    copied->get_stats(stats);
    set_stats(stats);
    alive_ = copied->alive_;
    row_ = copied->row_;
    place_ = copied->place_;
}

character::character(const char *name, const char *description, unsigned int *stats_array):entity(name, description)
{
    set_stats(stats_array);
    alive_ = true;
    row_=-1;
    place_=-1;
}

void character::set_max_hp(unsigned int value){max_hp_ = value;}
void character::set_current_hp(unsigned int value){current_hp_ = value;}
void character::set_max_sp(unsigned int value){max_sp_ = value;}
void character::set_current_sp(unsigned int value){current_sp_ = value;}
void character::set_atk(unsigned int value){atk_ = value;}
void character::set_def(unsigned int value){def_ = value;}
void character::set_s_atk(unsigned int value){s_atk_ = value;}
void character::set_s_def(unsigned int value){s_def_ = value;}
void character::set_initiative(unsigned int value){initiative_ = value;}
void character::set_stat(unsigned int value, unsigned int index)
{
    if(index<9)
    {
        *(&max_hp_+index) = value;
        alive_ = current_hp_>0 ? true : false;
    }
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
void character::set_stats(unsigned int stats_array[9]){memcpy(&max_hp_, stats_array, 9*sizeof (int));}
void character::set_alive(bool value){alive_ = value;}
void character::set_position(int r, int p)
{
    row_=r;
    place_=p;
}
unsigned int character::get_max_hp(){return max_hp_;}
unsigned int character::get_current_hp(){return current_hp_;}
unsigned int character::get_max_sp(){return max_sp_;}
int unsigned character::get_current_sp(){return current_sp_;}
unsigned int character::get_atk(){return atk_;}
unsigned int character::get_def(){return def_;}
unsigned int character::get_s_atk(){return s_atk_;}
unsigned int character::get_s_def(){return s_def_;}
unsigned int character::get_initiative(){return initiative_;}
unsigned int character::get_stat(unsigned int index)
{
    if(index<9){return *(&max_hp_+index);}
    else{return -1;}
}
void character::get_stats(unsigned int target_array[9]){memcpy(target_array, &max_hp_, 9*sizeof (int));}
bool character::alive(){return alive_;}

int character::get_row(){return row_;}

int character::get_place(){return place_;}

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
    unsigned int character_state[9];
    get_stats(character_state);
    for(int j=0; j<9; j++)
    {
        change[j] += character_state[j];
        change[j] = change[j]<0 ? 0 : change[j];
    }
    memcpy(character_state, change, 9*sizeof (int));
    for(unsigned int i=0; i<statuses_to_remove.size(); i++)
    {
        triggering_statuses_[statuses_to_remove[i]] = triggering_statuses_[triggering_statuses_.size()-(i+1)];
    }
    triggering_statuses_.erase(triggering_statuses_.end()-statuses_to_remove.size()+1, triggering_statuses_.end());
    set_stats(character_state);
    if(current_hp_ == 0){set_alive(false);}
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
    unsigned int character_state[9];
    get_stats(character_state);
    for(int j=0; j<9; j++)
    {
        change[j] += character_state[j];
        change[j] = change[j]<0 ? 0 : change[j];
    }
    memcpy(character_state, change, 9*sizeof (int));
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
