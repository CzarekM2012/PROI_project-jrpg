#ifndef ITEMS_DISPLAY_H
#define ITEMS_DISPLAY_H
#include "switchable_frame.h"
#include "item_frame.h"
#include "item_storage.h"

class items_display : public switchable_frame
{
    Q_OBJECT
public:
    items_display(item_storage *);
    item_frame *get_frame(int);
    void change_range(int value);
    void update();
private slots:
    void change_displayed_type();
    void pass_slot(entity*, int);
signals:
    void passed_slot(entity*, int);
private:
    item_frame *frames_[20];
    item_storage *storage_;
    int current_range_;
    bool equipment_;
};

#endif // ITEMS_DISPLAY_H
