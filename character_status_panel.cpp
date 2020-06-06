#include "character_status_panel.h"


character_status_panel::character_status_panel()
{
    layout_ = new QGridLayout();
    name_ = new QLabel();
    hp_ = new label_with_icon("health_icon");
    sp_ = new label_with_icon("skill_points_icon");
    action_ = new QProgressBar();
    action_->setTextVisible(false);
    this->setLayout(layout_);
    layout_->addWidget(name_, 0, 0);
    layout_->addWidget(hp_, 2, 0);
    layout_->addWidget(sp_, 4, 0);
    layout_->addWidget(action_, 6, 0);
    name_->setAlignment(Qt::AlignRight);
    hp_->label_->setAlignment(Qt::AlignRight);
    sp_->label_->setAlignment(Qt::AlignRight);
    layout_->setSpacing(0);
    layout_->setMargin(0);
}
void character_status_panel::paste_data(character *character)
{
    int character_stats[9];
    character->get_stats(character_stats);
    if(character_stats[0]>0)
    {
        name_->setText(character->get_name());
        char *text1 = new char[12], *text2 = new char[12];
        int_to_char_array(character_stats[1], text1);
        int_to_char_array(character_stats[0], text2);
        hp_->label_->setText(QString(text1) + QString("/") + QString(text2));
        int_to_char_array(character_stats[3], text1);
        int_to_char_array(character_stats[2], text2);
        sp_->label_->setText(QString(text1) + QString("/") + QString(text2));
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
