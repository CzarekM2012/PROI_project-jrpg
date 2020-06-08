#ifndef CHANGE_POSITION_PANEL_H
#define CHANGE_POSITION_PANEL_H
#include"party_display.h"
#include"switchable_frame.h"
#include"QPushButton"

class change_position_panel : public switchable_frame
{
    Q_OBJECT
public:
    change_position_panel(party *, entity*);
signals:
    void switch_places(std::pair<int, int>, std::pair<int, int>);
private slots:
    void pass_choice(entity*);
private:
    std::pair<int, int> changing_position_;
    party_display *display_;
    QPushButton *cancel_;
};

#endif // CHANGE_POSITION_PANEL_H
