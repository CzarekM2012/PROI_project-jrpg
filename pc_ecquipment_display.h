#ifndef PC_ECQUIPMENT_DISPLAY_H
#define PC_ECQUIPMENT_DISPLAY_H
#include "switchable_frame.h"
#include "item_frame.h"
#include "pc.h"

class pc_ecquipment_display : public switchable_frame
{
public:
    pc_ecquipment_display(), pc_ecquipment_display(pc *pc);
private:
    pc *displayed_pc_;
    item_frame *ecquipment_[7];
};

#endif // PC_ECQUIPMENT_DISPLAY_H
