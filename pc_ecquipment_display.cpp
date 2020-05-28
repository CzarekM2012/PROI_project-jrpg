#include "pc_ecquipment_display.h"

pc_ecquipment_display::pc_ecquipment_display(){}

pc_ecquipment_display::pc_ecquipment_display(pc *pc)
{
    displayed_pc_ = pc;
    int frames_coordinates[7][2]{{0, 1}, {1, 0}, {1, 1}, {1, 2}, {2, 0}, {2, 1}, {3, 1}};
    for(int i=0; i<7; i++)
    {
        ecquipment_[i] = new item_frame(displayed_pc_->get_part_of_ecquipment(i));
        layout_->addWidget(ecquipment_[i], frames_coordinates[i][0], frames_coordinates[i][1]);
    }
}
