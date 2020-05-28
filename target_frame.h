#ifndef TARGET_FRAME_H
#define TARGET_FRAME_H
#include <QFrame>
#include <QMouseEvent>
#include "character.h"
#include "item.h"

class target_frame : public QFrame
{
    Q_OBJECT
public:
    target_frame(), target_frame(item *);
    ~target_frame()=0;
    void set_represented_object(character *), set_represented_object(item *);
    entity* get_represented_object();
    std::pair<short int, short int> get_position();
    void set_standard_graphic(const char *type="");
protected:
    void enterEvent(QEvent *) override;
    void leaveEvent(QEvent *) override;
signals:
    void hover_in();
    void hover_out();
    void target_acquired(entity *);
protected:
    entity *represented_object_=nullptr;
};
#endif // TARGET_FRAME_H
