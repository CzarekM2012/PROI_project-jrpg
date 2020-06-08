#ifndef PC_CHOICE_PANEL_H
#define PC_CHOICE_PANEL_H
#include "switchable_frame.h"
#include "party_display.h"
#include <QPushButton>

class pc_choice_panel : public switchable_frame
{
public:
    pc_choice_panel(party *);
private:
    party_display *display_;
    QPushButton *cancel_, confirm_;
};

#endif // PC_CHOICE_PANEL_H
