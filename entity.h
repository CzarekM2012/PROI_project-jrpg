#ifndef ENTITY_H
#define ENTITY_H
#include <QString>
#include "status_effect.h"

class entity
{
public:
    entity(), entity(entity*), entity(const char *name, const char *description="");
    virtual ~entity()=0;
    QString get_name();
    QString get_description();
    void set_name(const char *name), set_name(QString name);
    void set_description(const char *graphic_directory), set_description(QString graphic_directory);
    virtual void set_max_hp(unsigned int value);
    virtual void set_current_hp(unsigned int value);
    virtual void set_max_sp(unsigned int value);
    virtual void set_current_sp(unsigned int value);
    virtual void set_atk(unsigned int value);
    virtual void set_def(unsigned int value);
    virtual void set_s_atk(unsigned int value);
    virtual void set_s_def(unsigned int value);
    virtual void set_initiative(unsigned int value);
    virtual void set_stat(unsigned int value, unsigned int index);
    virtual void set_stats(unsigned int *stats_array), set_stats();
    virtual void set_alive(bool value);
    virtual void set_position(int r, int p);
    virtual unsigned int get_max_hp();
    virtual unsigned int get_current_hp();
    virtual unsigned int get_max_sp();
    virtual unsigned int get_current_sp();
    virtual unsigned int get_atk();
    virtual unsigned int get_def();
    virtual unsigned int get_s_atk();
    virtual unsigned int get_s_def();
    virtual unsigned int get_initiative();
    virtual unsigned int get_stat(unsigned int index);
    virtual void get_stats(unsigned int *target_array);
    virtual bool alive();
    virtual int get_row();
    virtual int get_place();
    virtual std::pair<short int,short int> get_position();
    virtual void trigger_statuses();
    virtual void expire_statuses();
    virtual void add_status_effect(status_effect, bool);
    virtual short get_id();
private:
    QString name_, description_;
};

#endif // ENTITY_H
