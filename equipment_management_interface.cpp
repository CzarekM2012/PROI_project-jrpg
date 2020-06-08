#include "equipment_management_interface.h"

equipment_management_interface::equipment_management_interface(){}

equipment_management_interface::equipment_management_interface(party *party):switchable_frame()
{
    party_ = party;
    setStyleSheet("QFrame{border-color:black; border-width:2px; border-style:inset; background-color:darkblue}"
                  "target_frame{background-color:white}");
    create_widgets();
    place_widgets();
    connect_signals();
}

void equipment_management_interface::create_widgets()
{
    party_display_ = new party_display(party_);
    skills_display = new skill_choice_panel();
    stats_display_ = new full_stats_display();
    items_display_ = new items_display(party_->get_item_storage());
    pc_display_ = new pc_equipment_display();
    switch_places_ = new QPushButton("switch");
    switch_places_->setEnabled(false);
    equip_or_use_ = new QPushButton("equip/unequip");
    equip_or_use_->setEnabled(false);
    turn_equipment_page_left_ = new QPushButton("<-");
    turn_equipment_page_left_->setEnabled(false);
    turn_equipment_page_right_ = new QPushButton("->");
    switch_item_types_ = new QPushButton("consumables");
    close_ = new QPushButton("close");
}

void equipment_management_interface::place_widgets()
{
    layout_->addWidget(party_display_, 0, 0, 4, 6);
    layout_->addWidget(skills_display, 0, 6, 5, 10);
    layout_->addWidget(stats_display_, 5, 0, 3, 16);
    layout_->addWidget(items_display_, 8, 6, 9, 10);
    layout_->addWidget(pc_display_, 8, 0, 8, 6);
    layout_->addWidget(switch_places_, 4, 0, 1, 6);
    layout_->addWidget(equip_or_use_, 16, 0);
    layout_->addWidget(turn_equipment_page_left_, 16, 1);
    layout_->addWidget(turn_equipment_page_right_, 16, 2);
    layout_->addWidget(switch_item_types_, 16, 3);
    layout_->addWidget(close_, 16, 4);
}

void equipment_management_interface::connect_signals()
{
    connect(party_display_, SIGNAL(choosen_character(entity*)), this, SLOT(pass_character(entity*)));
    connect(this, SIGNAL(passed_character(pc*)), stats_display_, SLOT(display_character(pc*)));
    connect(this, &equipment_management_interface::passed_character, skills_display, [this](pc* pc){skills_display->display_skills(pc);});
    connect(this, &equipment_management_interface::passed_character, items_display_, [this](pc* pc)
    {
        if(pc!=nullptr)
        {
            items_display_->get_description()->setText(pc->get_description());
            return;
        }
        items_display_->get_description()->setText("");
    });
    connect(stats_display_, SIGNAL(unlock_equip()), this, SLOT(enable_equip()));
    connect(stats_display_, SIGNAL(lock_equip()), this, SLOT(disable_equip()));
    connect(items_display_, SIGNAL(passed_slot(entity*, int)), this, SLOT(item_choice(entity*, int)));
    connect(pc_display_, SIGNAL(passed_slot(entity*, int)), this,  SLOT(item_choice(entity*, int)));
    connect(pc_display_, &pc_equipment_display::passed_slot, items_display_, [this](entity *entity)
    {
        if(entity != nullptr)
        {
            items_display_->get_description()->setText(entity->get_description());
            return;
        }
        items_display_->get_description()->setText("");
    });
    connect(this, SIGNAL(passed_character(pc*)), pc_display_, SLOT(display_equipment(pc*)));
    connect(switch_places_, SIGNAL(clicked()), this, SLOT(prepare_positions_switch()));
    connect(turn_equipment_page_right_, &QPushButton::clicked, [this](){this->items_display_->change_range(20);
                                                                        turn_equipment_page_left_->setEnabled(true);});
    connect(items_display_, &items_display::lock_turn_right, this, [this](){turn_equipment_page_right_->setEnabled(false);});
    connect(turn_equipment_page_left_, &QPushButton::clicked, [this](){this->items_display_->change_range(-20);
                                                                       turn_equipment_page_right_->setEnabled(true);});
    connect(items_display_, &items_display::lock_turn_left, this, [this](){turn_equipment_page_left_->setEnabled(false);});
    connect(equip_or_use_, SIGNAL(clicked()), this, SLOT(use_item()));
    connect(switch_item_types_, SIGNAL(clicked()), this, SLOT(change_item_types()));
    connect(close_, SIGNAL(clicked()), this, SLOT(close()));
}

void equipment_management_interface::pass_character(entity *character)
{
    if(character->valid())
    {
        switch_places_->setEnabled(true);
        std::pair<int, int> position = character->get_position();
        choosen_character_ = party_->get_pc_address(position.first, position.second);
        emit passed_character(choosen_character_);
        return;
    }
    emit passed_character(nullptr);
    switch_places_->setEnabled(false);
}

void equipment_management_interface::enable_equip(){equip_or_use_->setEnabled(true);}

void equipment_management_interface::disable_equip(){equip_or_use_->setEnabled(false);}

void equipment_management_interface::item_choice(entity* item, int storage_slot)
{
    if(storage_slot < 0)
    {
        int temp = party_->get_item_storage()->get_equipment_slot(nullptr);
        if(temp != -1)
        {
            int item_type = item->get_type_of_eq();
            choosen_storage_slot_ = temp + 100*item_type;
            choosen_item_ = nullptr;
            int null_stats[9]={};
            equipment null("", null_stats, 0, item_type);
            stats_display_->display_item(&null);
        }
        return;
    }
    choosen_item_ = item;
    stats_display_->display_item(item);
    choosen_storage_slot_ = storage_slot;
}

void equipment_management_interface::change_item_types()
{
    equip_or_use_->setEnabled(false);
    stats_display_->update_stats();
    QString text = switch_item_types_->text();
    items_display_->change_displayed_type();
    if(text == QString("consumables"))
    {
        switch_item_types_->setText("equipment");
        equip_or_use_->setText("use");
        turn_equipment_page_left_->setEnabled(false);
        turn_equipment_page_right_->setEnabled(false);
        return;
    }
    switch_item_types_->setText("consumables");
    equip_or_use_->setText("equip/unequip");
    turn_equipment_page_left_->setEnabled(false);
    turn_equipment_page_right_->setEnabled(true);
}

void equipment_management_interface::use_item()
{
    equip_or_use_->setEnabled(false);
    std::pair<int, int> position = choosen_character_->get_position();
    pc *pc = party_->get_pc_address(position.first, position.second);
    item_storage *storage = party_->get_item_storage();
    if(choosen_item_ != nullptr)
    {
        if(choosen_item_->get_counter() == 0)
        {
            equipment *to_equip = storage->get_equipment(choosen_storage_slot_);
            equipment *removed = pc->equip(to_equip);
            storage->set_item(removed, choosen_storage_slot_);
            stats_display_->update_stats();
            items_display_->update();
            pc_display_->update();
            return;
        }
        consumable *to_consume = storage->get_consumable(choosen_storage_slot_);
        pc->consume(to_consume);
        //if(to_consume->get_counter()==0){storage->set_item(consumable(), choosen_storage_slot_);}
        stats_display_->update_stats();
        items_display_->update();
        return;
    }
    equipment *removed = pc->unequip(choosen_storage_slot_/100);
    storage->set_item(removed, choosen_storage_slot_%100);
    stats_display_->update_stats();
    items_display_->update();
    pc_display_->update();
}

void equipment_management_interface::prepare_positions_switch()
{
    disconnect(party_display_, SIGNAL(choosen_character(entity*)), this, SLOT(pass_character(entity*)));
    disconnect(items_display_, SIGNAL(passed_slot(entity*, int)), this, SLOT(item_choice(entity*, int)));
    disconnect(pc_display_, SIGNAL(passed_slot(entity*, int)), this,  SLOT(item_choice(entity*, int)));
    disconnect(this, SIGNAL(passed_character(pc*)), skills_display, SLOT(display_skills(pc*)));
    connect(party_display_, SIGNAL(choosen_character(entity*)), this, SLOT(switch_positions(entity*)));
    equip_or_use_->setEnabled(false);
    switch_places_->setEnabled(false);
}

void equipment_management_interface::switch_positions(entity *character)
{
    std::pair<int,int> position1 = choosen_character_->get_position(), position2 = character->get_position();
    if(position1!=position2)
    {
        switch_places_->setEnabled(false);
        party_->swap_members(position1, position2);
        party_display_->update();
        pc_display_->clear();
        stats_display_->clear();
        connect(party_display_, SIGNAL(choosen_character(entity*)), this, SLOT(pass_character(entity*)));
        connect(items_display_, SIGNAL(passed_slot(entity*, int)), this, SLOT(item_choice(entity*, int)));
        connect(pc_display_, SIGNAL(passed_slot(entity*, int)), this,  SLOT(item_choice(entity*, int)));
        connect(this, SIGNAL(passed_character(pc*)), skills_display, SLOT(display_skills(pc*)));
        disconnect(party_display_, SIGNAL(choosen_character(entity*)), this, SLOT(switch_positions(entity*)));
    }
}
