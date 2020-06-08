#ifndef ENTITY_H
#define ENTITY_H
#include <QString>
#include "status_effect.h"
#include "skill.h"

class entity
{
public:
    entity(), entity(entity*), entity(QString name, int*stats, QString description="");
    virtual ~entity()=0;
    QString get_name();
    QString get_description();
    void set_name(const char *name), set_name(QString name);
    void set_description(const char *graphic_directory), set_description(QString graphic_directory);
    virtual void set_stat(int value, unsigned int index);
    void set_stats(int *stats_array), set_stats();
    int get_stat(unsigned int index);
    void get_stats(int *target_array);

    virtual void set_alive(bool value);
    virtual void set_position(int r, int p);
    virtual bool alive();
    virtual bool valid();
    virtual std::pair<short int,short int> get_position();
    virtual void trigger_statuses();
    virtual void expire_statuses();
    virtual void add_status_effect(status_effect, bool);
    virtual short get_id();
    virtual entity *get_part_of_equipment(unsigned int);
    virtual skill *get_skill(int);
    virtual short get_type_of_eq();
    virtual int get_counter();
    virtual void decrease_counter(int amount=1);
private:
    int stats_[9]={}; //max_hp, current_hp, max_sp, current_sp, atk, def, s_atk, s_def, initiative
    QString name_, description_;
};

#endif // ENTITY_H
