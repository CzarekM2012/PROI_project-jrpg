#include "pc_equipment_display.h"

pc_equipment_display::pc_equipment_display()
{
    int frames_coordinates[7][2]{{0, 1}, {1, 1}, {2, 1}, {3, 1}, {2, 0}, {1, 0}, {1, 2}};
    for(int i=0; i<7; i++)
    {
        equipment_[i] = new item_frame(-i-1);
        layout_->addWidget(equipment_[i], frames_coordinates[i][0], frames_coordinates[i][1]);
        connect(equipment_[i], SIGNAL(choosen_slot(entity*, int)), this, SLOT(pass_slot(entity*, int)));
    }
}

void pc_equipment_display::display_equipment(pc *pc)
{
    displayed_pc_ = pc;
    update();
}

void pc_equipment_display::update()
{
    if(displayed_pc_ != nullptr)
    {
        for(int i=0; i<7; i++)
        {
            entity *temp = displayed_pc_->get_part_of_equipment(i);
            equipment_[i]->set_represented_object(temp);
            equipment_[i]->set_standard_graphic();
        }
        return;
    }
    for(int i=0; i<7; i++)
    {
        equipment_[i]->set_represented_object(nullptr);
        equipment_[i]->set_standard_graphic();
    }
}

void pc_equipment_display::clear()
{
    displayed_pc_ = nullptr;
    update();
}

void pc_equipment_display::pass_slot(entity* equipped, int index){emit passed_slot(equipped, index);}
