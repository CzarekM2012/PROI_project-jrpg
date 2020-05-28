#include "character_status_panel.h"


character_status_panel::character_status_panel()
{
    layout_ = new QGridLayout();
    name_ = new QLabel();
    hp_ = new QLabel();
    sp_ = new QLabel();
    action_ = new QProgressBar();
    action_->setTextVisible(false);
    this->setLayout(layout_);
    layout_->addWidget(name_, 0, 0);
    layout_->addWidget(hp_, 2, 0);
    layout_->addWidget(sp_, 4, 0);
    layout_->addWidget(action_, 6, 0);
    name_->setAlignment(Qt::AlignRight);
    hp_->setAlignment(Qt::AlignRight);
    sp_->setAlignment(Qt::AlignRight);
    layout_->setSpacing(0);
    layout_->setMargin(0);
}
void character_status_panel::paste_data(character *character)
{
    if(character->get_max_hp()>0)
    {
        name_->setText(character->get_name());
        char *text1 = new char[12], *text2 = new char[12];
        int temp = character->get_current_hp();
        int_to_char_array(temp, text1);
        int_to_char_array(character->get_max_hp(), text2);
        hp_->setText(QString(text1) + QString("/") + QString(text2));
        int_to_char_array(character->get_current_sp(), text1);
        int_to_char_array(character->get_max_sp(), text2);
        sp_->setText(QString(text1) + QString("/") + QString(text2));
        delete [] text1;
        delete [] text2;
    }
}

QProgressBar *character_status_panel::get_action_bar_(){return action_;}

void character_status_panel::highlight_on()
{
    name_->setStyleSheet("background-color:yellow");
}
void character_status_panel::highlight_off()
{
    name_->setStyleSheet("background-color:transparent");
}
