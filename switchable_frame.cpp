#include "switchable_frame.h"

switchable_frame::switchable_frame()
{
    layout_ = new QGridLayout();
    this->setLayout(layout_);
}

void switchable_frame::add_widget(QWidget *widget){layout_->addWidget(widget);}
void switchable_frame::add_widget(QWidget *widget, int row, int column, Qt::Alignment alignment){layout_->addWidget(widget, row, column, alignment);}
void switchable_frame::add_widget(QWidget *widget, int row, int column, int rowspan, int columnspan, Qt::Alignment alignment){layout_->addWidget(widget, row, column, rowspan, columnspan, alignment);}

void switchable_frame::set_stylesheet(const QString &stylesheet){this->setStyleSheet(stylesheet);}

void switchable_frame::get_margins(int *left, int *top, int *right, int *bottom){layout_->getContentsMargins(left, top, right, bottom);}
void switchable_frame::set_margins(int left, int top, int right, int bottom){layout_->setContentsMargins(left, top, right, bottom);}

void switchable_frame::set_spacing(int spacing){layout_->setSpacing(spacing);}
void switchable_frame::set_vSpacing(int spacing){layout_->setVerticalSpacing(spacing);}
void switchable_frame::set_hSpacing(int spacing){layout_->setHorizontalSpacing(spacing);}
