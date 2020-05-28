#ifndef ECQUIPMENT_MANAGEMENT_INTERFACE_H
#define ECQUIPMENT_MANAGEMENT_INTERFACE_H
#include "switchable_frame.h"
#include "party.h"
#include "party_display.h"
#include "full_stats_display.h"
#include "items_display.h"
#include "pc_ecquipment_display.h"

class ecquipment_management_interface : public switchable_frame
{
    Q_OBJECT
public:
    ecquipment_management_interface(), ecquipment_management_interface(party *party);
private slots:
    void display_pc_ecquipment(pc *pc);
private:
    party *party_;
    party_display *party_display_;
    full_stats_display *stats_display_;
    items_display *items_display_;
    pc_ecquipment_display *pc_display_;
};

#endif // ECQUIPMENT_MANAGEMENT_INTERFACE_H
