#include "character_frame.h"

character_frame::character_frame():QFrame()
{
    targeting_ = false;
    setMouseTracking(true);
}

character_frame::character_frame(character *represented_character):character_frame()
{
    represented_character_ = represented_character;
}

void character_frame::set_targeting(bool value){targeting_ = value;}

void character_frame::set_represented_character(character *character){represented_character_ = character;}

void character_frame::set_compound_style_sheet(QVector<QString> array_of_traits)
{
    QString stylesheet = array_of_traits[0];
    for(int i=1; i<array_of_traits.size(); i++)
    {
        stylesheet+= QString("; ") + array_of_traits[i];
    }
    setStyleSheet(stylesheet);
}

void character_frame::enterEvent(QEvent *event)
{
    emit hover_in();
    QWidget::enterEvent(event);
}
void character_frame::leaveEvent(QEvent *event)
{
    emit hover_out();
    QWidget::leaveEvent(event);
}

void character_frame::mousePressEvent(QMouseEvent *event)
{
    if(targeting_)
    {
        emit target_acquired(represented_character_);
    }
    QWidget::mousePressEvent(event);
}
