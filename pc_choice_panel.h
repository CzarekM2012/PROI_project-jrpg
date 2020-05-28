#ifndef PC_CHOICE_PANEL_H
#define PC_CHOICE_PANEL_H
#include "switchable_frame.h"
#include "party.h"
#include "target_frame.h"

class pc_choice_panel : public switchable_frame
{
public:
    pc_choice_panel(party *);
private:
    target_frame *formation_[3][2]={};
};

#endif // PC_CHOICE_PANEL_H
