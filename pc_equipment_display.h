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
    void clear();
private slots:
    void display_equipment(pc*);
    void pass_slot(entity*, int);
signals:
    void passed_slot(entity*, int);
private:
    pc *displayed_pc_;
    item_frame *equipment_[7];
};

#endif // PC_ECQUIPMENT_DISPLAY_H
