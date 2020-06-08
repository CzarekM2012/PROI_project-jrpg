#include "label_with_icon.h"

label_with_icon::label_with_icon()
{
    icon_ = new QFrame;
    label_ = new QLabel;
    layout_->addWidget(icon_, 0, 0, 1, 1);
    layout_->addWidget(label_, 0, 1, 1, 7);
    layout_->setSpacing(0);
    layout_->setContentsMargins(0, 0, 0, 0);
}

label_with_icon::label_with_icon(const char *icon, const char *text):label_with_icon()
{
    icon_->setStyleSheet(QString("border-image:url(:/images/") + QString(icon) + QString(".png)"));
    label_->setText(text);
}
