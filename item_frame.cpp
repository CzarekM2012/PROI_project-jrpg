#include "item_frame.h"

item_frame::item_frame()
{
    int w = width(), h = height();
    counter_ = new QLabel(this);
    counter_->setMaximumSize(w/5, h/5);
    counter_->move(4*w/5, 4*h/5);
}

item_frame::item_frame(equipment *item):item_frame(){change_item(item);}

item_frame::item_frame(QPair<consumable, int> *item):item_frame(){change_item(item);}

void item_frame::change_item(equipment *item)
{
    represented_item_ = item;
    set_standard_graphic();
    counter_->setText("");
}

void item_frame::change_item(QPair<consumable, int> *item)
{
    represented_item_ = &item->first;
    set_standard_graphic();
    char temp[4] = "x";
    int_to_char_array(item->second, &temp[1]);
    counter_->setText(QString(temp));
}

void item_frame::mousePressEvent(QMouseEvent *event)
{
    if(represented_item_!=nullptr){emit choosen_item(represented_item_);}
    QWidget::mousePressEvent(event);
}
