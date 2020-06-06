#ifndef FULL_STATS_DISPLAY_H
#define FULL_STATS_DISPLAY_H
#include "pc.h"
#include "switchable_frame.h"
#include "data_processing.h"
#include "label_with_icon.h"

class full_stats_display : public switchable_frame
{
    Q_OBJECT
public:
    full_stats_display();
    void display_equipment(entity*);
    void update_stats();
private slots:
    void display_character(pc*);

signals:
    void unlock_equip();
    void lock_equip();
private:
    pc* represented_character_=nullptr;
    QLabel *name_;
    label_with_icon* stat_[7];
};

#endif // FULL_STATS_DISPLAY_H
