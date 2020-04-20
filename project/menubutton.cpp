#include "menubutton.h"
#include <QString>
#include <QWidget>
#include <QLayout>
MenuButton::MenuButton(const QString &text, QWidget *parent, QSize *min_size, QLayout *layout):QPushButton(text, parent)
{
    if(min_size!=nullptr)
    {
        this->setMinimumSize(*min_size);
    }
    if(layout!=nullptr)
    {
        layout->addWidget(this);
    }
}

MenuButton::~MenuButton()
{
}
