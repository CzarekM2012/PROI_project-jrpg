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
    // int/int to char array custom function(start from max_stat to speed up the process;
    name_->setText(*character->get_name());
    set_current_stat_over_max_stat_text(hp_, character->get_current_hp(), character->get_max_hp());
    set_current_stat_over_max_stat_text(sp_, character->get_current_sp(), character->get_max_sp());
}

void character_status_panel::set_current_stat_over_max_stat_text(QLabel *label, int nominator, int denominator)
{
    int mul = 10, number_of_digits = 1;
    while(denominator/mul >= 1)
    {
        mul*=10;
        number_of_digits++;
    }
    mul/=10;
    char array[2*number_of_digits+2];
    array[number_of_digits] = '/';
    array[2*number_of_digits+1] = 0;
    int i=0;
    bool nominator_left_side_zero = true;
    while(mul > 0)
    {
        char nominator_digit = nominator/mul, denominator_digit = denominator/mul;
        nominator %= mul;
        denominator %= mul;
        mul/=10;
        if(nominator_left_side_zero && nominator_digit == 0){nominator_digit = ' ';}
        else
        {
            nominator_left_side_zero = false;
            nominator_digit += '0';
        }
        denominator_digit += '0';
        array[i]=nominator_digit;
        array[number_of_digits+1+i]=denominator_digit;
        i++;
    }
    label->setText(QString(array));
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
