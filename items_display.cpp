#include "items_display.h"

items_display::items_display():current_range_(0)
{
    description_ = new QLabel;
    description_->setStyleSheet("background-color:white");
    layout_->addWidget(description_, 0, 0, 1, 5);
    for(int i=0; i<20; i++)
    {
        frames_[i] = new item_frame;
        layout_->addWidget(frames_[i], 1+(i/5*2), i%5, 2, 1);
        connect(frames_[i], SIGNAL(choosen_slot(entity*, int)), this, SLOT(pass_slot(entity*, int)));
        connect(frames_[i], &item_frame::choosen_slot, this, [this](entity *item){description_->setText(item->get_description());});
    }
}

items_display::items_display(item_storage *storage, bool in_battle):items_display()
{
    storage_ = storage;
    if(!in_battle)
    {
        equipment_ = true;
        update();
        return;
    }
    equipment_ = false;
    display_battle_items();
}

item_frame *items_display::get_frame(int index){return frames_[index];}

void items_display::change_range(int value)
{
    if(equipment_)
    {
        if(current_range_+value>0)
        {
            if(current_range_+value<60){current_range_+=value;}
            else
            {
                current_range_ = 60;
                emit lock_turn_right();
            }
        }
        else
        {
            current_range_=0;
            emit lock_turn_left();
        }
        update();
    }
}

void items_display::change_displayed_type()
{
    equipment_ = equipment_ ? false : true;
    current_range_ = 0;
    update();
}

QLabel *items_display::get_description(){return description_;}

void items_display::update()
{
    if(equipment_)
    {
        for(int i=0; i<20; i++)
        {
            frames_[i]->set_represented_object(storage_->get_equipment(current_range_+i));
            frames_[i]->update();
        }
        return;
    }
    for(int i=0; i<20; i++)
    {
        frames_[i]->set_represented_object(storage_->get_consumable(i));
        frames_[i]->update();
    }
}

void items_display::display_battle_items()
{
    consumable *battle_items[20]={};
    int j=0;
    for(int i=0; i<20; i++)
    {
        consumable *temp = storage_->get_consumable(i);
        if(temp != nullptr && temp->battle_item())
        {
            battle_items[j] = temp;
            j++;
        }
    }
    for(int i=0; i<j; i++)
    {
        frames_[i]->set_represented_object(battle_items[i]);
        frames_[i]->update();
    }
}

void items_display::pass_slot(entity *item, int index){emit passed_slot(item, current_range_+index);}
