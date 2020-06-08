#ifndef CHOOSE_CONSUMABLE_PANEL_H
#define CHOOSE_CONSUMABLE_PANEL_H
#include "items_display.h"
#include "QPushButton"
#include "switchable_frame.h"
#include "skill.h"

class choose_consumable_panel : public switchable_frame
{
    Q_OBJECT
public:
    choose_consumable_panel(item_storage *);
private slots:
    void generate_item_originating_skill_(entity*, int);
signals:
    void give_skill(skill*, entity*);
private:
    items_display *display_;
    QPushButton *choose_, *cancel_;
    entity *used_item;
    skill *generated_=nullptr;
};

#endif // CHOOSE_CONSUMABLE_PANEL_H
