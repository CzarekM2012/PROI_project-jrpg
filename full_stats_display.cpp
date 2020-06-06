#include "full_stats_display.h"

full_stats_display::full_stats_display()
{
    const char *temp[7]={"health_icon", "skill_points_icon", "attack_icon",
                          "defense_icon", "special_attack_icon", "special_defense_icon", "initiative_icon"};
    const int coords[7][2]={{1, 0},{2, 0},{1, 1},{1, 2},{2, 1},{2, 2},{1, 3}};
    name_ = new QLabel;
    name_->setAlignment(Qt::AlignRight);
    layout_->addWidget(name_, 0, 0);
    for(int i=0; i<7; i++)
    {
        stat_[i] = new label_with_icon(temp[i]);
        stat_[i]->label_->setAlignment(Qt::AlignRight);
        layout_->addWidget(stat_[i], coords[i][0], coords[i][1]);
    }
    setStyleSheet("QLabel{background-color:white}");
}

void full_stats_display::display_character(pc* pc)
{
    represented_character_ = pc;
    name_->setText(represented_character_->get_name());
    update_stats();
    emit lock_equip();
}

void full_stats_display::display_equipment(entity* equipment)
{
    if(represented_character_ != nullptr)
    {
        int pc_stats[9], new_pc_stats[9];
        represented_character_->get_stats(pc_stats);
        if(!represented_character_->calculate_stats_after_equip(equipment, new_pc_stats)){return;}
        char *text1 = new char[12], *text2 = new char[12], *text3 = new char[12], *text4 = new char[12];
        int_to_char_array(pc_stats[1], text1);
        int_to_char_array(pc_stats[0], text2);
        int_to_char_array(new_pc_stats[1], text3);
        int_to_char_array(new_pc_stats[0], text4);
        stat_[0]->label_->setText(QString(text1)+QString("/")+QString(text2)+QString("  ->  ")+QString(text3)+QString("/")+QString(text4));
        int_to_char_array(pc_stats[3], text1);
        int_to_char_array(pc_stats[2], text2);
        int_to_char_array(new_pc_stats[3], text3);
        int_to_char_array(new_pc_stats[2], text4);
        stat_[1]->label_->setText(QString(text1)+QString("/")+QString(text2)+QString("  ->  ")+QString(text3)+QString("/")+QString(text4));
        for(int i=2; i<7; i++)
        {
            int_to_char_array(pc_stats[i+2], text1);
            int_to_char_array(new_pc_stats[i+2], text2);
            stat_[i]->label_->setText(QString(text1)+QString("  ->  ")+QString(text2));
        }
        emit unlock_equip();
        delete[] text1;
        delete[] text2;
        delete[] text3;
        delete[] text4;
    }
}

void full_stats_display::update_stats()
{
    int stats[9];
    represented_character_->get_stats(stats);
    char *text1 = new char[12], *text2 = new char[12];
    int_to_char_array(stats[1], text1);
    int_to_char_array(stats[0], text2);
    stat_[0]->label_->setText(QString(text1)+QString("/")+QString(text2));
    int_to_char_array(stats[3], text1);
    int_to_char_array(stats[2], text2);
    stat_[1]->label_->setText(QString(text1)+QString("/")+QString(text2));
    for(int i=2; i<7; i++)
    {
        int_to_char_array(stats[i+2], text1);
        stat_[i]->label_->setText(QString(text1));
    }
    delete[] text1;
    delete[] text2;
}
