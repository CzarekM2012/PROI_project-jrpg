#ifndef STATUS_EFFECT_H
#define STATUS_EFFECT_H
#include <QString>

class status_effect
{
public:
    status_effect(int stats[9], int duration);
    void set_stats(int stats[9]);
    void set_duration(unsigned int duration);
    bool decrease_duration();
    void get_stats(int target_array[9]);
    unsigned int get_duration();
private:
    int affected_stats_[9];
    unsigned int duration_;
};

#endif // STATUS_EFFECT_H
