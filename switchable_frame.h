#ifndef SWITCHABLE_FRAME_H
#define SWITCHABLE_FRAME_H
#include <QObject>
#include <QFrame>
#include <QGridLayout>

class switchable_frame : public QFrame
{
    Q_OBJECT
public:
    switchable_frame();
    QGridLayout *layout_;
signals:
    void close_signal(switchable_frame*);
    void switch_back();

};

#endif // SWITCHABLE_FRAME_H
