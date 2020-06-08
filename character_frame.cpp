#include "character_frame.h"

character_frame::character_frame():target_frame(), state_(0){}

character_frame::character_frame(character *character, short initial_state):target_frame(), state_(initial_state){represented_object_ = character;}

void character_frame::set_state(short value){state_ = value;}

void character_frame::update(short target_state)
{
    if(state_!=0)
    {
        forced_update(target_state);
    }
}

void character_frame::forced_update(short target_state)
{
    set_state(target_state);
    QWidget::update();
}

short character_frame::state(){return state_;}

void character_frame::mousePressEvent(QMouseEvent *event)
{
    if(state_>5){emit target_acquired(represented_object_);}
    QWidget::mousePressEvent(event);
}

void character_frame::paintEvent(QPaintEvent *event)
{
    if(state_ > 1 && state_ !=6)
    {
        QPainter painter;
        int w = width(), h = height();
        painter.begin(this);
        QBrush brush(Qt::BrushStyle::SolidPattern);
        switch (state_)
        {
            case 2:{brush.setColor("lightblue"); break;}
            case 3:{brush.setColor("darkblue"); break;}
            case 4:{brush.setColor("red"); break;}
            case 5:{brush.setColor("darkgreen"); break;}
            case 7:{brush.setColor("lightblue"); break;}
            case 8:{brush.setColor("yellow"); break;}
            case 9:{brush.setColor("lightgreen"); break;}
        }
        painter.setPen(QPen(brush, 5));
        painter.drawEllipse(QPoint(w/2, h/2), w/4, h/4);
        if(state_ > 2 && state_ != 6)
        {
            painter.drawLine(w/2, h/4, w/2, h-h/4);
            painter.drawLine(w/4, h/2, w-w/4, h/2);
        }
        painter.end();
    }
    QFrame::paintEvent(event);
}

void character_frame::is_target(entity *entity)
{
    if(represented_object_->valid())
    {
        if(state_ > 1)
        {
            if(entity == represented_object_)
            {
                if(state_ >= 6)
                {
                    update(state_-4);
                }
            }
            else
            {
                if(state_ < 6)
                {
                    update(state_+4);
                }
            }
        }
    }
}
