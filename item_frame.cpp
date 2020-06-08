#include "item_frame.h"

item_frame::item_frame(int index):target_frame(), index_(index){place_counter();}

item_frame::item_frame(equipment *equipment, int index):target_frame(equipment), index_(index){place_counter();}

item_frame::item_frame(consumable *consumable, int index):target_frame(consumable), index_(index){place_counter(represented_object_->get_counter());}

int item_frame::get_index(){return index_;}

void item_frame::set_counter(int number){counter_->setNum(number);}

void item_frame::clear()
{
    represented_object_=nullptr;
    update();
}

void item_frame::update()
{
    int number = represented_object_==nullptr ? 0 : represented_object_->get_counter();
    if(number !=0){counter_->setNum(number);}
    else{counter_->setText("");}
    set_standard_graphic();
}

void item_frame::mousePressEvent(QMouseEvent *event)
{
    if(represented_object_!=nullptr){emit choosen_slot(represented_object_, index_);}
    QWidget::mousePressEvent(event);
}

void item_frame::place_counter(int number)
{
    int w = width(), h = height();
    counter_ = new QLabel(this);
    counter_->setAlignment(Qt::AlignRight);
    counter_->setStyleSheet("border-width:0px; border-image:none; background-color:transparent");
    if(number!=0){counter_->setNum(number);}
    counter_->setNum(1000);
    counter_->move(x() + w/2,y() + h/2);
}


