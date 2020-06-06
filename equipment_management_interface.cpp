#include "equipment_management_interface.h"

equipment_management_interface::equipment_management_interface(){}

equipment_management_interface::equipment_management_interface(party *party):switchable_frame()
{
    party_ = party;
    create_widgets();
    place_widgets();
    connect_signals();
    setStyleSheet("QFrame{border-color:black; border-width:2px; border-style:inset; background-color:darkblue} target_frame{background-color:white}");
}

void equipment_management_interface::pass_character(entity *character)
{
    std::pair<int, int> position = character->get_position();
    choosen_character_ = party_->get_pc_address(position.first, position.second);
    emit passed_character(choosen_character_);
}

void equipment_management_interface::create_widgets()
{
    party_display_ = new party_display(party_);
    stats_display_ = new full_stats_display();
    items_display_ = new items_display(party_->get_item_storage());
    pc_display_ = new pc_equipment_display();
    switch_places_ = new QPushButton("switch");
    equip_or_use_ = new QPushButton("equip");
    equip_or_use_->setEnabled(false);
    confirm_switch_ = new QPushButton("confirm");
    turn_equipment_page_left_ = new QPushButton("<-");
    turn_equipment_page_right_ = new QPushButton("->");
    switch_item_types_ = new QPushButton("consumables");
    close_ = new QPushButton("close");
    /*mapper_ = new QSignalMapper(this);
    mapper_->map(turn_equipment_page_right_, 20)*/
}

void equipment_management_interface::place_widgets()
{
    layout_->addWidget(party_display_, 0, 0, 6, 2);
    layout_->addWidget(stats_display_, 6, 0, 3, 8);
    layout_->addWidget(items_display_, 9, 3, 8, 5);
    layout_->addWidget(pc_display_, 9, 0, 8, 3);
    layout_->addWidget(switch_places_, 1, 2);
    layout_->addWidget(equip_or_use_, 17, 0);
    layout_->addWidget(confirm_switch_, 2, 2);
    layout_->addWidget(turn_equipment_page_left_, 17, 1);
    layout_->addWidget(turn_equipment_page_right_, 17, 2);
    layout_->addWidget(switch_item_types_, 17, 3);
    layout_->addWidget(close_, 17, 4);
}

void equipment_management_interface::connect_signals()
{
    connect(party_display_, SIGNAL(choosen_character(entity*)), this, SLOT(pass_character(entity*)));
    connect(this, SIGNAL(passed_character(pc*)), stats_display_, SLOT(display_character(pc*)));
    connect(this, SIGNAL(passed_character(pc*)), pc_display_, SLOT(display_equipment(pc*)));
    connect(items_display_, SIGNAL(passed_slot(entity*, int)), this, SLOT(item_choice(entity*, int)));
    connect(stats_display_, SIGNAL(unlock_equip()), this, SLOT(enable_equip()));
    connect(stats_display_, SIGNAL(lock_equip()), this, SLOT(disable_equip()));
    connect(turn_equipment_page_right_, &QPushButton::clicked, [this](){this->items_display_->change_range(20);});
    connect(turn_equipment_page_left_, &QPushButton::clicked, [this](){this->items_display_->change_range(-20);});
    connect(equip_or_use_, SIGNAL(clicked()), this, SLOT(use_item()));
    connect(close_, SIGNAL(clicked()), this, SLOT(close()));
}

void equipment_management_interface::enable_equip(){equip_or_use_->setEnabled(true);}

void equipment_management_interface::disable_equip(){equip_or_use_->setEnabled(false);}

void equipment_management_interface::use_item()
{
    if(choosen_item_->get_counter() == 0)
    {
        equip_or_use_->setEnabled(false);
        std::pair<int, int> position = choosen_character_->get_position();
        pc *pc = party_->get_pc_address(position.first, position.second);
        item_storage *storage = party_->get_item_storage();
        int index = storage->get_equipment_slot(choosen_item_);
        equipment *to_equip = storage->get_equipment(index);
        equipment *removed = pc->equip(to_equip);
        storage->set_item(removed, index);
        stats_display_->update_stats();
        items_display_->update();
        pc_display_->update();
    }
}

void equipment_management_interface::item_choice(entity* item, int storage_slot)
{
    choosen_item_ = item;
    stats_display_->display_equipment(item);
    choosen_storage_slot_ = storage_slot;
}

void equipment_management_interface::close(){emit close_signal(this);}
