#ifndef ECQUIPMENT_MANAGEMENT_INTERFACE_H
#define ECQUIPMENT_MANAGEMENT_INTERFACE_H
#include "switchable_frame.h"
#include "party.h"
#include "party_display.h"
#include "full_stats_display.h"
#include "items_display.h"
#include "pc_equipment_display.h"
#include <QPushButton>

class equipment_management_interface : public switchable_frame
{
    Q_OBJECT
public:
    equipment_management_interface(), equipment_management_interface(party *party);
private slots:
    void pass_character(entity*);
    void enable_equip();
    void disable_equip();
    void use_item();
    void close();
    void item_choice(entity*, int);
signals:
    void passed_character(pc*);
    void passed_equipment(entity*);
private:
    void create_widgets();
    void place_widgets();
    void connect_signals();
    party *party_;
    party_display *party_display_;
    full_stats_display *stats_display_;
    items_display *items_display_;
    pc_equipment_display *pc_display_;
    QPushButton *switch_places_, *equip_or_use_, *confirm_switch_, *turn_equipment_page_right_, *turn_equipment_page_left_, *switch_item_types_, *close_;
    pc *choosen_character_;
    entity *choosen_item_;
    int choosen_storage_slot_;
};

#endif // ECQUIPMENT_MANAGEMENT_INTERFACE_H
