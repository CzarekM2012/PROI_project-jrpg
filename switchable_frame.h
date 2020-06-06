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
signals:
    void close_signal(switchable_frame*);
    void switch_back();
protected:
    QGridLayout *layout_;
};

#endif // SWITCHABLE_FRAME_H
