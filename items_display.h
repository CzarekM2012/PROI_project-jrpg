#ifndef ITEMS_DISPLAY_H
#define ITEMS_DISPLAY_H
#include "switchable_frame.h"
#include "item_frame.h"
#include "item_storage.h"

class items_display : public switchable_frame
{
    Q_OBJECT
public:
    items_display(), items_display(item_storage *, bool in_battle=false);
    item_frame *get_frame(int);
    void change_range(int value);
    void update();
    void change_displayed_type();
    QLabel *get_description();
private slots:
    void pass_slot(entity*, int);
signals:
    void passed_slot(entity*, int);
    void lock_turn_right();
    void lock_turn_left();
private:
    void display_battle_items();
    QLabel *description_;
    item_frame *frames_[20];
    item_storage *storage_;
    int current_range_;
    bool equipment_;
};

#endif // ITEMS_DISPLAY_H
