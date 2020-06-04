#ifndef SWITCHABLE_FRAME_H
#define SWITCHABLE_FRAME_H
#include <QObject>
#include <QFrame>
#include <QGridLayout>

class switchable_frame : public QFrame
{
public:
    switchable_frame();
//protected:
    QGridLayout *layout_;
};

#endif // SWITCHABLE_FRAME_H
