#include "switchable_frame.h"

switchable_frame::switchable_frame()
{
    layout_ = new QGridLayout();
    this->setLayout(layout_);
}
