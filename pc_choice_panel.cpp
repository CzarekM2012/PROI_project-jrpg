#include "pc_choice_panel.h"

pc_choice_panel::pc_choice_panel(party *party)
{
    display_ = new party_display(party);
}
