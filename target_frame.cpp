#include "target_frame.h"


target_frame::target_frame():QFrame(){setMouseTracking(true);}

target_frame::~target_frame(){}

void target_frame::set_represented_object(character *character){represented_object_ = character;}

void target_frame::set_represented_object(item *item){represented_object_ = item;}

entity* target_frame::get_represented_object(){return represented_object_;}

/*void target_frame::set_compound_style_sheet(QVector<QString> array_of_traits)
{
    QString stylesheet = array_of_traits[0];
    for(int i=1; i<array_of_traits.size(); i++)
    {
        stylesheet+= QString("; ") + array_of_traits[i];
    }
    setStyleSheet(stylesheet);
}*/

void target_frame::set_standard_graphic(const char *type_of_graphic)
{
    if(represented_object_ != nullptr)
    {
        setStyleSheet(QString("border-image:url(:/images/") + represented_object_->get_name() + QString(type_of_graphic) + QString(".png)"));
    }
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
