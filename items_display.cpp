#include "items_display.h"

items_display::items_display(item_storage *storage): current_range_(0), equipment_(true)
{
    storage_ = storage;
    for(int i=0; i<20; i++)
    {
        frames_[i] = new item_frame(storage->get_equipment(i), i);
        layout_->addWidget(frames_[i], i/5, i%5);
        frames_[i]->set_standard_graphic();
        connect(frames_[i], SIGNAL(choosen_slot(entity*, int)), this, SLOT(pass_slot(entity*, int)));
    }
}

item_frame *items_display::get_frame(int index){return frames_[index];}

void items_display::change_range(int value)
{
    if(current_range_+value>0)
    {
        if(current_range_+value<60){current_range_+=value;}
        else{current_range_ = 60;}
    }
    else{current_range_=0;}
    update();
}

void items_display::change_displayed_type()
{
    equipment_ = equipment_ ? false : true;
    update();
}

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

void items_display::pass_slot(entity *item, int index){emit passed_slot(item, current_range_+index);}
