#include "target_frame.h"


target_frame::target_frame():QFrame(){setMouseTracking(true);}

target_frame::target_frame(entity *entity):target_frame(){represented_object_ = entity;}

target_frame::~target_frame(){}

void target_frame::set_represented_object(entity *entity){represented_object_ = entity;}

entity* target_frame::get_represented_object(){return represented_object_;}

void target_frame::set_standard_graphic(const char *type_of_graphic)
{
    if(represented_object_ != nullptr)
    {
        setStyleSheet(QString("border-image:url(:/images/") + represented_object_->get_name() + QString(type_of_graphic) + QString(".png)"));
        return;
    }
    setStyleSheet("");
}

void target_frame::enterEvent(QEvent *event)
{
    emit hover_in();
    QWidget::enterEvent(event);
}

void target_frame::leaveEvent(QEvent *event)
{
    emit hover_out();
    QWidget::leaveEvent(event);
}
