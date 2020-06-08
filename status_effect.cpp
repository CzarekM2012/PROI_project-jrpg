#include "status_effect.h"

status_effect::status_effect(int stats[9], int duration): duration_(duration){set_stats(stats);}

void status_effect::set_stats(int stats[9]){memcpy(affected_stats_, stats, 9*sizeof (int));}

void status_effect::set_duration(unsigned int duration){duration_ =duration;}

bool status_effect::decrease_duration(){return --duration_==0;}

void status_effect::get_stats(int target_array[9]){memcpy(target_array, affected_stats_, 9*sizeof (int));}

unsigned int status_effect::get_duration(){return duration_;}
