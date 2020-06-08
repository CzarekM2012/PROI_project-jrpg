#ifndef LABEL_WITH_ICON_H
#define LABEL_WITH_ICON_H
#include<QLabel>
#include"switchable_frame.h"

class label_with_icon : public switchable_frame
{
public:
    label_with_icon(), label_with_icon(const char *icon, const char *text="");
    QLabel *label_;
private:
    QFrame *icon_;
};

#endif // LABEL_WITH_ICON_H
