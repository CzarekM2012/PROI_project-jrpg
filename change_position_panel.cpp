#include "change_position_panel.h"

change_position_panel::change_position_panel(party *party, entity* pc)
{
    changing_position_ = pc->get_position();
    display_ = new party_display(party);
    cancel_ = new QPushButton("close");
    layout_->addWidget(display_, 0, 0, 4, 6);
    layout_->addWidget(cancel_, 4, 0, 1, 6);
    connect(display_, SIGNAL(choosen_character(entity*)), this, SLOT(pass_choice(entity*)));
    connect(cancel_, &QPushButton::clicked, this, [this](){close();});
    setStyleSheet("QFrame{border-color:black; border-width:2px; border-style:inset; background-color:darkblue} QLabel{background-color:white}");
}

void change_position_panel::pass_choice(entity* pc)
{
    std::pair<int,int> temp = pc->get_position();
    if(temp != changing_position_)
    {
        emit switch_places(changing_position_, temp);
        close();
    }
}
