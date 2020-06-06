#ifndef PC_ECQUIPMENT_DISPLAY_H
#define PC_ECQUIPMENT_DISPLAY_H
#include "switchable_frame.h"
#include "item_frame.h"
#include "pc.h"

class pc_equipment_display : public switchable_frame
{
    Q_OBJECT
public:
    pc_equipment_display(), pc_equipment_display(pc *pc);
    void update();
private slots:
    void display_equipment(pc*);
private:
    pc *displayed_pc_;
    item_frame *equipment_[7];
};

#endif // PC_ECQUIPMENT_DISPLAY_H
