#ifndef PARTY_DISPLAY_H
#define PARTY_DISPLAY_H
#include "switchable_frame.h"
#include "character_frame.h"
#include "party.h"

class party_display : public switchable_frame
{
    Q_OBJECT
public:
    party_display(party*);
    void update();
private slots:
    void pass_choice(entity*);
signals:
    void choosen_character(entity*);
private:
    party *party_=nullptr;
    character_frame *formation_[3][2]={};
};

#endif // PARTY_DISPLAY_H
